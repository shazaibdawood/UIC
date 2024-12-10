#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//---------------------------------------------------------------------
// getArgs() - Retrieve & store command line arguments
// inputs/outputs:
//    int argc          number of args, including program executable name
//    char* argv[]      array of strings
//    int* rowPtr       first command line parameter - integer number of rows
//    char* charPtr     second command line parameter - character symbol to use
//    bool* triTypePtr  third command line parameter - triangle type: 0=isosceles 1=right
// default: 5 rows, using '*', isosceles triangle
//    set to default values if any command line parameter is missing

void getArgs(int argc, char* argv[], int* rowPtr, char* charPtr, bool* triTypePtr) {
    
    if(argc != 4){
        printf("Invalid number of command line parameters.\nUsing default values...\n");
        *rowPtr = 5;
        *charPtr = '*';
        *triTypePtr = false;
        return;
    }
    
    *rowPtr = atoi(argv[1]);
    *charPtr = *argv[2];
    *triTypePtr = atoi(argv[3]);
    return;
}

//---------------------------------------------------------------------
int main(int argc, char* argv[]) {
    int rows;
    char myChar;
    bool triType;
    
    getArgs(argc, argv, &rows, &myChar, &triType);

    //print a triangle - variables
    //   rows: height of triangle
    //   myChar: character to make triangle with
    //   triType: 0/false = isosceles, 1/true = right
    for (int i = 1; i <= rows; ++i) {
        int k = 0;
        for (int s = 1; s <= rows - i; ++s) {
            printf("  ");
        }
        
        int cap = 2 * i - 1;
        if (triType) {
            cap = i;
        }
        
        while (k < cap) {
            printf("%c ",myChar);
            ++k;
        }
        printf("\n");
    }

  return 0;
}