#include <stdio.h>

int main(void) {
   char inputFileName[25];
   char line[25];  
   FILE* inFile = NULL;

   // Get the name of the input file
   scanf("%s", inputFileName);

   // Open the input file
   inFile = fopen(inputFileName, "r");

   // Print contents of input file
   while(!feof(inFile)) {
       fgets(line, 25, inFile);
       printf("%s", line);
   }

   fclose(inFile);
   return 0;
}