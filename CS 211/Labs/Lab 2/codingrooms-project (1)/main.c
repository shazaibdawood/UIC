#include <stdio.h>

int main() {
    int skip, sz;
    int nums[100];
    
    //skip: #bytes two skip between successive characters of the  
    //      secret message in the bytes of nums[]
    //sz:   number of integers that will be entered into nums[] array; 
    //      assume sz <= 100
    scanf("%d %d",&skip, &sz);
    
    for (int i = 0; i < sz; ++i) {
        scanf("%d",&nums[i]);
    }

    printf("Secret Message: ");

    //TODO: use a pointer to work through nums[] 1-byte at-a-time;
    //      after skipping the specified number of bytes (int skip), 
    //      interpret the next byte as a char and print it to screen;
    //      repeat this process for the entire nums[] array to reveal
    //      a hidden secret message.
    //      TIP: use a pointer type that jumps only a single byte for 
    //           each incrementation step. This will require pointer
    //           type casting.
    
    int* firstElement = nums;
    char* split;
    split = (char*)firstElement;

    for(int i = skip; i < 4 * sz; i += skip + 1){
        // char code = *(split + i);
        printf("%c", *(split + i));
    }

    printf("\n");
    
    return 0;
}
