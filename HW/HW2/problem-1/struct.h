#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INDCLUDED

#include <stdio.h>
#define SIZE 20
typedef struct {
   char lastName[SIZE];
   char firstName[SIZE];
   float height;
} Person;

void Init_Person(Person *this, float h, char *firstN, char *lastN);

void Print(Person *array[], int sizeOfArray);

int HeightComp(const void *a, const void *b);

int NameComp(const void *a, const void *b);

void FillFromSTDin(char *choice);

void ScanIn(char *fileInput, char *choice);

void SortBy(Person *array[], int size, char *choice);

void Delete(Person *array[], int sizeOfArray);

#endif
