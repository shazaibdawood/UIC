#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SelectionSort(int numbers[], int numbersSize) {
    int i;
    int j;
    int indexSmallest;
    int temp;      // Temporary variable for swap
   
    for (i = 0; i < numbersSize - 1; ++i) {
        // Find index of smallest remaining element
        indexSmallest = i;
        for (j = i + 1; j < numbersSize; ++j) {
            if ( numbers[j] < numbers[indexSmallest] ) {
                indexSmallest = j;
            }
        }
        // Swap numbers[i] and numbers[indexSmallest]
        temp = numbers[i];
        numbers[i] = numbers[indexSmallest];
        numbers[indexSmallest] = temp;
    }
}

void Merge(int numbers[], int i, int j, int k) {
    int mergedSize = k - i + 1;       // Size of merged partition
    int mergedNumbers[mergedSize];    // Temporary array for merged numbers
    int mergePos;                     // Position to insert merged number
    int leftPos;                      // Position of elements in left partition
    int rightPos;                     // Position of elements in right partition
   
    mergePos = 0;
    leftPos = i;                      // Initialize left partition position
    rightPos = j + 1;                 // Initialize right partition position
   
    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (numbers[leftPos] < numbers[rightPos]) {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        } else {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos; 
        }
        ++mergePos;
    }
   
    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }
   
    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }
   
    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
}

void MergeSort(int numbers[], int i, int k) {
    int j;
   
    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition
      
        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);
      
        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}

int main() {
    const int ARRAY_SIZE = 50000; //, or 100000

    time_t t0, t1, t2;

    int arr[ARRAY_SIZE];
    srand((int)time(0)); // use a unique seed

    time(&t0);
    printf("Building array of size %d with random values...\n",ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = rand();
    }
    
    printf("Sorting with SelectionSort...\n");
    SelectionSort(arr,ARRAY_SIZE);
    time(&t1);   
    printf("Filling array again with random values\n AND Sorting with MergeSort, 200 times...\n");
       
    for (int j = 0; j < 200; j++) {
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            arr[i] = rand();
        }
        
        MergeSort(arr,0,ARRAY_SIZE-1);
    }
    time(&t2);
    
    printf("\n");
    printf("Timing summary:\n");
    printf("   build initial array & SelectionSort: %.0f second(s)\n",difftime(t1,t0));
    printf("   refill array & MergeSort, 200 times: %.0f second(s)\n",difftime(t2,t1));
    printf("\n");
        
    return 0;
}
