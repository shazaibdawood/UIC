#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode_struct {
      int data; //stored in this node
      struct ListNode_struct* next; //a link to the next node in the list
} ListNode;

void arrayAppend(int* arr, int* size, int val) {
    arr[*size] = val;
    (*size)++;
}

int* fillArrayByAppend(int numVals) {
    int* arr = (int*)malloc(numVals*sizeof(int));
    int size = 0;
    for (int i = 0; i < numVals; i++) {
        arrayAppend(arr, &size, rand());
    }
    return arr;
}

void arrayPrepend(int* arr, int* size, int val) {
    for (int i = *size; i > 0; i--) {
        arr[i] = arr[i-1];
    }
    arr[0] = val;
    (*size)++;
}

int* fillArrayByPrepend(int numVals) {
    int* arr = (int*)malloc(numVals*sizeof(int));
    int size = 0;
    for (int i = 0; i < numVals; i++) {
        arrayPrepend(arr, &size, rand());
    }
    return arr;
}

void arrayInsertInOrder(int* arr, int* size, int val) {
    int ind = 0;
    while (ind < *size && arr[ind] < val) {
        ind++;
    }
    for (int i = *size; i > ind; i--) {
        arr[i] = arr[i-1];
    }
    arr[ind] = val;
    (*size)++;
}

int* fillArrayInOrder(int numVals) {
    int* arr = (int*)malloc(numVals*sizeof(int));
    int size = 0;
    for (int i = 0; i < numVals; i++) {
        arrayInsertInOrder(arr, &size, rand());
    }
    return arr;
}

void listAppend(ListNode** head, int val) {
    //--------------------------------------------------------
    // DONE: listAppend() should allocate space for a  
    //          new ListNode and set the data subitem to the
    //          input <val>, then insert the new node at the 
    //          back of the list with head node <head>; this 
    //          function must handle edge case(s), such as an
    //          empty <head> list
    //--------------------------------------------------------

    // to get stared, the new node allocation is provided
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data=val;
    newNode->next=NULL;
    if (*head == NULL) { 
      *head = newNode;
      return;
    }
   else{
    ListNode* last=*head;
    while(last->next != NULL){
    last=last->next;
   }
    last->next=newNode;
   }
}

ListNode* fillListByAppend(int numVals) {
    ListNode* head = NULL;
    for (int i = 0; i < numVals; i++) {
        listAppend(&head, rand());
    }
    return head;
}

void listPrepend(ListNode** head, int val) {
    //--------------------------------------------------------
    // DONE: listPrepend() should allocate space for a  
    //          new ListNode and set the data subitem to the
    //          input <val>, then insert the new node at the 
    //          front of the list with head node <head>; this 
    //          function must handle edge case(s), such as an
    //          empty <head> list
    //--------------------------------------------------------

    // to get stared, the new node allocation is provided
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data=val;
    newNode->next=(*head);
    (*head)=newNode;
}

ListNode* fillListByPrepend(int numVals) {
    ListNode* head = NULL;
    for (int i = 0; i < numVals; i++) {
        listPrepend(&head, rand());
    }
    return head;
}

void listInsertInOrder(ListNode** head, int val) {
    //--------------------------------------------------------
    // TODO: listInsertInOrder() should allocate space for a  
    //          new ListNode and set the data subitem to the
    //          input <val>, then insert the new node into the
    //          sorted list with head node <head>, maintaining
    //          the sorted (i.e. non-decreasing values) nature 
    //          of the list; this function must handle edge 
    //          case(s), such as an empty <head> list
    //--------------------------------------------------------
    
    // to get stared, the new node allocation is provided
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
     newNode->data=val;
     newNode->next=NULL;
    if (*head == NULL) { 
      *head = newNode;
      return;
    }
   else{
    ListNode* last=*head;
     if (val <= (*head)->data) {
        newNode->next=*head;
        *head=newNode;
        return;
    }
    while (last->next!= NULL && last->next->data<val){
        last=last->next;
    }
    newNode->next=last->next;
    last->next=newNode;
}
}

ListNode* fillListInOrder(int numVals) {
    ListNode* head = NULL;
    for (int i = 0; i < numVals; i++) {
        listInsertInOrder(&head, rand());
    }
    return head;
}


void displayArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("  %d %d\n", i, arr[i]);
    }
}

void displayList(ListNode* list) {
    ListNode* curr = list;
    int i = 0;
    while (curr != NULL) {
        printf("  %d %d\n", i, curr->data);
        i++;
        curr = curr->next;
    }
}

void freeList(ListNode* list) {
    //--------------------------------------------------------
    // DONE: freelist() should free all heap-allocated memory
    //          for all ListNodes* in the input <list> 
    //--------------------------------------------------------
    ListNode* freeing;
    while (list!= NULL){
        freeing=list;
        list=list->next;
        free(freeing);
    }
}


int main(int argc, char* argv[]) {
    // seeding the random number generator..
    //  replace this with srand(time(0)) for even more "randomness"
    //  but keep the seed 123456 for submitting to autograder
    srand(123456); 
    
    // using command-line argument to set #values; default = 20
    int numVals = 20;
    if (argc > 1) {
        numVals = atoi(argv[1]);
    }

//------------------------------------------------
// Building array and list using append
//------------------------------------------------
    printf("\nBuilding an array using append...\n");
    int* arr1 = fillArrayByAppend(numVals);
    if (numVals < 25) {
        displayArray(arr1, numVals);
    }

    printf("\nBuilding a list using append...\n");
    ListNode* list1 = fillListByAppend(numVals);
    if (numVals < 25) {
        displayList(list1);
    }

    free(arr1);
    freeList(list1);

//------------------------------------------------
// Building array and list using prepend
//------------------------------------------------
    printf("\nBuilding an array using prepend...\n");
    int* arr2 = fillArrayByPrepend(numVals);
    if (numVals < 25) {
        displayArray(arr2, numVals);
    }

    printf("\nBuilding a list using prepend...\n");
    ListNode* list2 = fillListByPrepend(numVals);
    if (numVals < 25) {
        displayList(list2);
    }

    free(arr2);
    freeList(list2);

//------------------------------------------------
// Building array and list using sorted insert
//------------------------------------------------
    printf("\nBuilding a sorted array using ordered insert...\n");
    int* arr3 = fillArrayInOrder(numVals);
    if (numVals < 25) {
        displayArray(arr3, numVals);
    }

    printf("\nBuilding a sorted list using ordered insert...\n");
    ListNode* list3 = fillListInOrder(numVals);
    if (numVals < 25) {
        displayList(list3);
    }

    free(arr3);
    freeList(list3);

    return 0;
}
