#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {

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
}
