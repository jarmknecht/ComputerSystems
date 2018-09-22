/* Bubble sort: Pointer version 
 change anywhere there is an array element ie data reference to a pointer 
 Part A*/

void BubblePtr(long *data, long count) {
	long *i = 0;
	long *last = 0;

	for (last = count - 1; last > data; last--) { //do while last is greater than num elements in data the start point of the data
       for (i = data; i < last; i++) {
       	if (*(i + 1) < *i) {
       		long t = *(i + 1);
       		*(i + 1) = *i;
       		*i = t;
       	}
       }
	}
}