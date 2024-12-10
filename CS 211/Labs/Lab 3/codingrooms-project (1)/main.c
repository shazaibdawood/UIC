#include <stdio.h>
#include <stdlib.h>

int main(void) {

    //sz = # of integers to follow, to be read into the nums array
    int sz;
    scanf("%d",&sz); 

    //TODO #1: allocate nums, an integer array of size sz, on the heap.
    //         DO NOT use square bracket array notation []; instead, use
    //          dynamic memory allocation & assign a pointer to the array
    //         An example for a double array of size 7 is provided here; 
    //          this is just an example and MUST be modified or removed
    double* arr = (double*)malloc(sizeof(double)*7);
    
    //the array pointed to by nums will contain sz integers, 
    //  whose bytes contain a three-line secret message

    //TODO #2: fill the nums array w/ values scanned in from user input.
    //         DO NOT use square bracket array notation []; instead, use
    //          a pointer, distinct from the array pointer declared in 
    //          the dynamic memory allocation step above, to work
    //          through the array memory, assigning integers as you go 

    
    printf("Line 1: ");
    //TODO #3: begin at the *first* byte of the nums array,
    //          print out every third byte interpreted as a char
    //          until the end of the nums array, 
    //          which contains sz integers.
    //         DO NOT use square bracket array notation []; instead, use
    //          a pointer and increment it through nums 1-byte at-a-time


    printf("\n");

    printf("Line 2: ");
    //TODO #4: use the same pointer from Line 1; begin at the 
    //          *second-to-last* byte of the nums array, working 
    //          backwards through nums, printing out every third byte 
    //          interpreted as a char until the front of the nums array, 
    //          which contains sz integers.
    //         DO NOT use square bracket array notation []; increment a
    //          pointer through nums, in reverse, 1-byte at-a-time


    printf("\n");

    printf("Line 3: ");
    //TODO #5: use the same pointer from Lines 1 & 2; begin at the 
    //          *third* byte of the nums array, working through nums, 
    //          printing out every third byte interpreted as a char 
    //          until the back of the nums array, 
    //          which contains sz integers.
    //         DO NOT use square bracket array notation []; increment a
    //          pointer through nums 1-byte at-a-time


    printf("\n");

    //TODO #6: free all memory that was dynamically allocated on the heap
    

    return 0;
}


