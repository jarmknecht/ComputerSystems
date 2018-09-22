/*
Jonathan Armknecht, Section 1, jonathan.armknecht@gmail.com
Test case 1:
   Input: 21 1 2 3 4 5
   Expected Output: Will say array size is too large and quit.
   Output was correct.
Test case 2:
   Input: 0 1 2 3 4
   Expected Output: nothing will be printed because the array size is zero.
   Output was correct.
Test case 3:
   Input: 4 50 100 30 4
   Expected Output: The array contents will be printed in numerical order 4 30 50 100.
   Output was correct.
*/

#include <stdio.h>
#include <stdlib.h>

int ComparatorFunc(const void *a, const void *b) { //arguments are constants so the pointer aren't changed just compared
   return (*(int*)a - *(int*)b);
}

int main(int argc, char* argv[]) {
   int arrSize = 0;

   printf("Input size of array first and then numbers to go into array. Array cannot be larger than 20. (Ex 4 2 5 7 9): ");
   fscanf(stdin, "%d", &arrSize);
   
   if (arrSize > 20) {
     fprintf(stderr, "Array size of %d is too big. Cannot be bigger than 20. Exiting...\n", arrSize);
     exit(1);
   }

  /* error called instead
     while(arrSize > 20) {
      while ((getchar()) != '\n'); //this ensures the the stdin buffer is flushed so it can take new input
      printf("Array size is too large try again: ");
      fscanf(stdin, "%d", &arrSize);
   }*/

   int array[arrSize]; // array has to be initialized after knowing its size 

   for (int i = 0; i < arrSize; ++i) {
      if (getchar() == '\n') {
         fprintf(stderr, "Incorrect amount of numbers entered. Exiting...\n");
         exit(1);
      }
      fscanf(stdin, "%d", &array[i]);
   }

   qsort(array, arrSize, sizeof(int), ComparatorFunc);

   printf("Contents of array are: ");
   
   for (int i = 0; i < arrSize; ++i) {
      printf("%d ", array[i]);
   }
   
   printf("\n");

   return 0;
 }
