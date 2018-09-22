/*
 * My solution implements the implicit free list found
 * within the book. This last week has been very hectic
 * so I did not have enough time to figure out a solution
 * to the explicity free list allocator.
 * This allocator uses an implicit free list, a first fit placement into the heap,
 * and boundary tag coalescing. Block boundaries are aligned to be double words (8 bytes).
 * Minimum block size is 16 bytes. Both allocated and free blocks are constructed the same way
 * Each has a header and footer that tells the size of the block and if it is allocated or not,
 * a payload that holds the data, and optional padding. The hold heap has a prologue block
 * and an epilogue block that tells where the heap starts and ends respectively.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

// Macros from the book to help with pointer arithmetic in computing
// addresses along with other helpful macros for manipulating the free list

#define WSIZE 4 // Word size in bytes also header and footer size
#define DSIZE 8 // Double word size in bytes
#define CHUNKSIZE (1 << 12) // Used to extend the heap by this amount in bytes

#define MAX(x, y) ((x) > (y) ? (x) : (y))

//This combines a size of a block and the allocator bit into a header or footer
#define PACK(size, alloc) ((size) | (alloc))

//Returns the word that is referenced by a pointer
#define GET(p) (*(unsigned int *)(p))

//Stores the value val into the block pointed to by p
#define PUT(p, val) (*(unsigned int *)(p) = (val))

//Returns the size of the block from the header or footer
#define GET_SIZE(p) (GET(p) & ~0x7)

//Returns the allocated bit to see if it is allocated or not
#define GET_ALLOC(p) (GET(p) & 0x1)

//The rest of these macros work on the payload pointed to by block pointers

//Returns a pointer to the block header
#define HDRP(bp) ((char *)(bp) - WSIZE)

//Returns a pointer to the block footer
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

//Returns the block pointer of the next block
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))

//Returns the block pointer of the previous block
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

static char *heap_listp = 0;  /* Pointer to first block */ 

/* Helper functions */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void checkheap(int verbose);
static void printblock(void *bp);
static void checkblock(void *bp);

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "Armknecht",
    /* First member's full name */
    "Jonathan Armknecht",
    /* First member's email address */
    "jonthan.armknecht@gmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/* 
 * mm_init - initialize the malloc package/initialize the heap to be
 * used by mm_malloc, mm_realloc, and mm_free
 */
int mm_init(void) {
	/* Create the initial empty heap */
	if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *) -1) {
		return -1; //unsuccessful allocation of the heap
	}
	/* Four words are obtained from memory to initialize the heap */
	PUT(heap_listp, 0); // Padding for alignment
	PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); // Beginning of heap header
	PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); // Beginning of heap footer
	PUT(heap_listp + (3 * WSIZE), PACK(0, 1)); // End of heap header
	heap_listp += (2 * WSIZE);

	/* Extend the empty heap with a free block of CHUNKSIZE bytes, creates the 
	 * initial free block
	 */
	if (extend_heap(CHUNKSIZE / WSIZE) == NULL) {
		return -1; 
	}

    return 0;
}

/*
 * *extend_heap is called 1) when the heap is initialized
 * and 2) when mm_malloc can't find any space in the current heap
 */

static void *extend_heap(size_t words) {
	char *bp;
	size_t size;

	/* Allocates an even amount of words to maintain correct alignment within heap 
	 * This ensures that the requested size is a multiple of 2 words (8 bytes) */
	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	if ((long)(bp = mem_sbrk(size)) == -1) {
		return NULL; // Reached the end of the heap
	}

	/* Initialize free block's header, footer and epilogue header */
	PUT(HDRP(bp), PACK(size, 0)); //Make header
	PUT(FTRP(bp), PACK(size, 0)); //Make footer
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); //Make epilogue header

	/* Coalesce if previous block was free */
	return coalesce(bp);
}


/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size) {
	size_t asize; //The adjusted block size
	size_t extendsize; //Amount to extend heap if there is no fit
	char *bp;

	/* Ignore bad requests */
	if (size == 0) {
		return NULL; //no pointer to allocate since size is zero
	}

	/* Adjust the size of the block to include alignment requirements and headers/footers */
	if (size <= DSIZE) {
		asize = 2 * DSIZE; //Enforce minimum block size of 16 bytes (8 for alignment and 8 for header and footer)
	}
	else { //Request is over 8 bytes add in overhead of header and footer (8 bytes) and then round to nearest multiple of 8
		asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
	}

	/* Search free list for a fit by first fit technique */
	if ((bp = find_fit(asize)) != NULL) {
		place(bp, asize); //place block and split excess
		return bp;
	}

	/* No fit was found. Need more memory for the heap */
	extendsize = MAX(asize, CHUNKSIZE);
	if ((bp = extend_heap(extendsize / WSIZE)) == NULL) {
		return NULL; //no more memory can be used
	}
	place(bp, asize); //place block and split excess
	return bp;


    /*int newsize = ALIGN(size + SIZE_T_SIZE);
    void *p = mem_sbrk(newsize);
    if (p == (void *)-1)
	return NULL;
    else {
        *(size_t *)p = size;
        return (void *)((char *)p + SIZE_T_SIZE);
    }*/
}

/*
 * Uses a first fit search to see if there is room in the heap to add the new block
 */
static void *find_fit(size_t asize) {
	void *bp;

	for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) { //searches through the list of blocks
		if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
			//if block isn't allocated and the asize if less or equal to size found in the header found a fit
			return bp;
		}
	}
	return NULL; //No fit found
}

/*
 * Used to place the new block into the heap when there is room to do so
 */
static void place(void *bp, size_t asize) {
	size_t csize = GET_SIZE(HDRP(bp));

	if ((csize - asize) >= (2 * DSIZE)) {
		//splits the block based on if the remainder of the block after the split is greater or equal to 16 bytes
		PUT(HDRP(bp), PACK(asize, 1)); //set as allocate in the header of the new block in the heap
		PUT(FTRP(bp), PACK(asize, 1)); //set as allocate in the footer of the new block in the heap
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK(csize - asize, 0)); //split the remaining and set header as unallocated
		PUT(FTRP(bp), PACK(csize - asize, 0)); //split the remaining and set footer as unallocated
	}
	else { //if remainder less than 16 bytes (minimum block size) don't split it
		PUT(HDRP(bp), PACK(csize, 1));
		PUT(FTRP(bp), PACK(csize, 1));
	}
}

/*
 * mm_free - Freeing a block does nothing.
 * Frees the requested block and then merges adjacent
 * free blocks using the boundary-tags coalescing technique
 */
void mm_free(void *bp) {
	size_t size = GET_SIZE(HDRP(bp)); //Get the size of the block that is being freed

	PUT(HDRP(bp), PACK(size, 0)); //Make the header say it is unallocated now
	PUT(FTRP(bp), PACK(size, 0)); //Make the footer say it is unallocated now
	coalesce(bp); //combine adjacent free block into one block
}

/* A helper function that is called when freeing blocks or when extending the heap
 * size. It uses the boundary-tags coalescing technique that checks the four cases
 * of wheter a freed block Case 1) has no previous or next block free Case 2) the next block is
 * free Case 3) the previous block is free and Case 4) both the previous and the next blocks are
 * free.
 * Because my free list has both a prologue and an epilogue block I don't
 * have to check the edge conditions for when the requested block is at the beginning
 * or the end of the heap.
 */

static void *coalesce(void *bp) {
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))); //Gets footer of previous block to see if allocated or not
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp))); //Gets the header of the next block to see if allocated or not
	size_t size = GET_SIZE(HDRP(bp)); //Get the size of the block you are trying to coalesce

	/* Case 1 */
	if (prev_alloc && next_alloc) { //if prev_alloc is 1 and next_alloc is 1 nothing to coalesce
		return bp;
	}
	/* Case 2 */
	else if (prev_alloc && !next_alloc) { // prev is 1 and next is 0 coalesce with next block
		size += GET_SIZE(HDRP(NEXT_BLKP(bp))); //add to the old block the size of the next block to make new sized block
		PUT(HDRP(bp), PACK(size, 0)); //set the header as new size and unallocated
		PUT(FTRP(bp), PACK(size, 0)); //set the footer as new size and unallocated
	}
	/* Case 3 */
	else if (!prev_alloc && next_alloc) { //prev is 0 and next is 1 coalesce with prev block
		size += GET_SIZE(HDRP(PREV_BLKP(bp))); //add to the old block the size of the prev block to make new sized block
		PUT(FTRP(bp), PACK(size, 0)); //set footer as new size and unallocated
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0)); //set prev header as new size and unallocated
		bp = PREV_BLKP(bp); //set block pointer as prev pointer for a new free block
	}

	/* Case 4 */
	else { //both prev and next are 0 so coalesce with both
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) + //adds the size of the prev and next blocks to the size of the old block
			GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0)); //set header of prev to size and unallocated
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0)); //set footer of next to size and unallocated
		bp = PREV_BLKP(bp); //set block pointer as prev pointer for the new free block
	}
	return bp;
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size) {
    size_t oldsize;
    void *newptr;

    /* If the size is 0 it is just a call to free and NULL is returned */
    if (size == 0) {
    	mm_free(ptr);
    	return 0;
    }

    /* If the ptr is NULL than it is just a call to malloc */
    if (ptr == NULL) {
    	return mm_malloc(size);
    }

    newptr = mm_malloc(size);

    /* If newptr is NULL/0 than realloc failed and the original block is left alone */
    if (!newptr) {
    	return 0;
    }

    /* Copy the old data into the new block */
    oldsize = GET_SIZE(HDRP(ptr)); //Get the size of the payload from the ptr's header
    if (size < oldsize) {
    	oldsize = size;
    }
    memcpy(newptr, ptr, oldsize); //copy contents of memory
    mm_free(ptr); //free old block

    return newptr;

    /*void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;*/
}

/* Funtion that prints out the header and footer of block indicated by bp */
static void printblock(void *bp) {
	size_t hsize; //holds header size
	size_t halloc; //holds alloc bit in header
	size_t fsize; //holds footer size
	size_t falloc; //holds alloc bit in footer

	checkheap(0);
	hsize = GET_SIZE(HDRP(bp));
	halloc = GET_ALLOC(HDRP(bp));  
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));

    if (hsize == 0) { //nothing is in the block so just print pointer
    	printf("%p: EOL\n", bp);
    	return;
    }

    //This prints the pointer of the header and footer and wheter or not it is allocated 'a' or free 'f'
    printf("%p: header: [%p:%c] footer: [%p:%c]\n", bp, 
	hsize, (halloc ? 'a' : 'f'), 
	fsize, (falloc ? 'a' : 'f'));
}

/* Checks to see that alignment is followed and headers match footers */
static void checkblock(void *bp) {
	if ((size_t)bp % 8) {
		printf("Error: %p is not doubleword aligned\n", bp);
	}
    if (GET(HDRP(bp)) != GET(FTRP(bp))) {
    	printf("Error: header does not match footer\n");
    }
}

/* Checks the heap for consistency, this is essentially my mm_check funtion
 * but instead of returning zero it prints out error messages associated with the error
 * if it fails.
 */
static void checkheap(int verbose) {
	char *bp = heap_listp;

    if (verbose) {
		printf("Heap (%p):\n", heap_listp);
	}

    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
		printf("Bad prologue header\n");
	}

    checkblock(heap_listp);

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
		if (verbose) {
	    	printblock(bp);
		}
	checkblock(bp);
    }

    if (verbose) {
		printblock(bp);
	}

    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) {
		printf("Bad epilogue header\n");
	}
}


