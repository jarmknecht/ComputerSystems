#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 20

void Init_Person(Person *this, float h, char *firstN, char *lastN) {
   this->height = h;
   strncpy(this->lastName, lastN, SIZE);
   strncpy(this->firstName, firstN, SIZE);
}

void Print(Person *array[], int sizeOfArray) {
   for (int i = 0; i < sizeOfArray; i++) {
      printf("%s, %s  %f\n", array[i]->lastName, array[i]->firstName, array[i]->height);
   }
}

int HeightComp(const void *a, const void *b) {
   Person *A = *(Person **)a;
   Person *B = *(Person **)b;
   if (fabs(A->height - B->height) <= 0.000001) { //basically same height if diff smaller than num
     return 0;
   }
   return A->height > B->height ? 1 : -1;
}

int NameComp(const void *a, const void *b) {
   Person *A = *(Person **)a;
   Person *B = *(Person **)b;
   return strcmp(A->lastName, B->lastName);
}

void FillFromSTDin(char *choice) {
    FILE* fp;
    int sizeOfArray;
    char lName[SIZE];
    char fName[SIZE];
    float pHeight;

    fp = stdin;

    fscanf(fp, "%d", &sizeOfArray);
    Person* array[sizeOfArray];
    for (int i = 0; i < sizeOfArray; i++) {
      Person* p = (Person *)malloc(sizeof(Person));
      fscanf(fp, "%s", fName);
      fscanf(fp, "%s", lName);
      fscanf(fp, "%f", &pHeight);
      array[i] = p;
      Init_Person(array[i], pHeight, fName, lName);
   }
   
   SortBy(array, sizeOfArray, choice);
   Print(array, sizeOfArray);
   Delete(array, sizeOfArray);
}

void ScanIn(char *fileInput, char *choice) {
   FILE *text;
   int sizeOfArray;
   char lName[SIZE];
   char fName[SIZE];
   float pHeight;   

   text = fopen(fileInput, "r");
   if (text == NULL) {
      fprintf(stderr, "Could not open file %s\n", fileInput);
      exit(1);
   }
   fscanf(text, "%d", &sizeOfArray);

   Person* array[sizeOfArray];
   
   for (int i = 0; i < sizeOfArray; i++) {
      Person* p = (Person *)malloc(sizeof(Person));
      fscanf(text, "%s", fName);
      fscanf(text, "%s", lName);
      fscanf(text, "%f", &pHeight);
      array[i] = p;
      Init_Person(array[i], pHeight, fName, lName);
   }
   fclose(text);
   SortBy(array, sizeOfArray, choice);
   Print(array, sizeOfArray);
   Delete(array, sizeOfArray);
}

void Delete(Person *array[], int sizeOfArray) {
   for (int i = 0; i < sizeOfArray; i++) {
      free(array[i]);
   }
}

void SortBy(Person *array[], int size, char *choice) {
  if (strcmp(choice, "last") == 0) {
    qsort(array, size, sizeof(char *), NameComp);
  }
  else if (strcmp(choice, "height") == 0) {
    qsort(array, size, sizeof(float *), HeightComp);
  }
  else {
    fprintf(stderr, "Incorrect choice for sorting\n");
    exit(1);
  }
}

/*int main (int argc, char* argv[]) {

   if (argc > 3 || argc < 2) {
     fprintf(stderr, "Incorrect amount of arguments\n");
     exit(1);
   }

   if (argc == 2) {
     FillFromSTDin(argv[1]);
   }

   if (argc == 3) {
     ScanIn(argv[2], argv[1]);
   }

   return 0;
}*/
