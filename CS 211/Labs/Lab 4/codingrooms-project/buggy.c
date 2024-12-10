/* File: buggy.c
 * --------------
 * Intentionally buggy code to observe under Valgrind.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayArray(int* arr, int sz) {
    for (int i = 0; i < sz; ++i) {
        printf("%d ", arr[i]);
    }
}

void make_error_1(int n) {
    printf("--- Making error 1: write past end of stack-allocated array\n\n");
   
    int buf[5];
    for (int i = 0; i < n; ++i) {
        buf[i] = rand() % 10;
    }
    printf("address %p of stack array size 5, contents ", buf);
    displayArray(buf, n);
    printf(" uses size %d\n", n);
}

void make_error_2(int n)
{
    printf("--- Making error 2: write past end of heap-allocated memory\n\n");
   
    int* ptr = malloc(5*sizeof(int));
    for (int i = 0; i < n; ++i) {
        ptr[i] = rand() % 10;
    }
    printf("ptr %p of heap memory array size 5, contents ", ptr);
    displayArray(ptr, n);
    printf(" uses size %d\n", n);
    free(ptr);
}

void make_error_3(void)
{
    printf("--- Making error 3: using unitialized heap-allocated memory\n\n");
   
    int* ptr = malloc(5*sizeof(int));

    printf("ptr %p of heap memory array size 5 points to ",ptr);
    if (ptr[0] < 0) {
        printf("non-");    
    }
    printf("postive value with contents ");
    displayArray(ptr, 5);
    free(ptr);
}

void make_error_4(void)
{
    printf("--- Making error 4: use pointer to freed heap memory\n\n");

    int* ptr = malloc(10*sizeof(int));
    for (int i = 0; i < 10; ++i) {
        ptr[i] = rand() % 10;
    }
    free(ptr);
    
    printf("ptr %p to heap memory, contents = \n", ptr);
    displayArray(ptr, 10);
    printf("\n");
}

void make_error_5(void)
{
    printf("--- Making error 5: double free heap memory\n\n");

    int* ptr = malloc(10*sizeof(int));
    for (int i = 0; i < 10; ++i) {
        ptr[i] = rand() % 10;
    }
    printf("ptr %p to heap memory, contents = \n", ptr);
    displayArray(ptr, 10);
    free(ptr);
    
    printf("\n");
    free(ptr);
}

void make_error_6(void)
{
    printf("--- Making error 6: no free of heap memory\n\n");

    int* ptr = malloc(10*sizeof(int));
    for (int i = 0; i < 10; ++i) {
        ptr[i] = rand() % 10;
    }

    printf("ptr %p to heap memory, contents = \n", ptr);
    displayArray(ptr, 10);
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Missing command-line argument.\n");
        return -1;
    }
    
    int opt = atoi(argv[1]);
    int num = 0;
    if (argc > 2) {
        num = atoi(argv[2]);
    }
    
    srand(time(0));
    switch(opt) {
        case 1: make_error_1(num); return 0;
        case 2: make_error_2(num); return 0;
        case 3: make_error_3(); return 0;
        case 4: make_error_4(); return 0;
        case 5: make_error_5(); return 0;
        case 6: make_error_6(); return 0;
        default: printf("required command-line argument is number 1, 2, 3, 4, 5, or 6\n"); return -2;
    }
}