#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node_struct {
    int num;
    struct Node_struct* next;
    struct Node_struct* prev;
} Node;

bool isCyclic(Node* head) {
    //------------------------------------------------
    // TODO: isCyclic() should return true if the list 
    //          with head node <head> has a cycle; 
    //          return false if there is no cycle.
    //              This function must work for 
    //              singly-linked lists, where all
    //              <prev> pointers are NULL
    //------------------------------------------------
    if((head) == NULL || (head)->next == NULL){
        return false;
    }

    struct Node_struct* turtle = (head);
    struct Node_struct* rabbit = (head)->next;
    int counter = 0;
    while(rabbit != NULL){
        if(rabbit == turtle){
            return true;
        }
        rabbit = rabbit->next;

        if(counter % 2 == 0){
            turtle = turtle->next;
        }
        counter++;
    }
    
    return false;
}

Node* convertToDoublyLinkedList(Node* head) {
    //-------------------------------------------------
    // TODO: convertToDoublyLinkedList() should convert
    //          a singly-linked Node list <head> to
    //          a doubly-linked list; that is, when the
    //          function is called, the <next> pointers
    //          link the nodes, but the <prev> pointers
    //          are all NULL; there are two results of 
    //          the conversion to a doubly-linked list:
    //              1. the <prev> pointer for each node
    //                 is a set to point to the 
    //                 previous node in the list; 
    //                 Ex: list = 0->1->2->/
    //                     for node 0,   next -> 1
    //                                 & prev -> NULL
    //                     for node 1,   next -> 2
    //                                 & prev -> 0
    //                     for node 2,   next -> NULL
    //                                 & prev -> 1
    //              2. a pointer to the last node 
    //                 (i.e. the tail of the list)
    //                 is returned, for future list 
    //                 traversal in reverse
    //                 Ex: list = 0->1->2->/
    //                     return a pointer to node 2
    //-----------------------------------------------
    struct Node_struct* tail;
    if(head == NULL){
        head->prev = NULL;
        tail = head;
        return tail;
    }

    head->prev = NULL;
    struct Node_struct* temp1 = head;
    struct Node_struct* temp2 = head->next;
    while(temp2 != NULL){
        temp2->prev = temp1;
        temp1 = temp2;
        temp2 = temp2->next;
    }

    tail = temp1;
    return tail;
}



void printList(Node* head) {
    const int MAX_LIST_SIZE = 8;
    Node* curr = head;
    int count = 0;
    while (curr != NULL && count < MAX_LIST_SIZE+2) {
        printf("%d -> ",curr->num);
        curr = curr->next;
        count++;
    }
    if (curr == NULL) {
        printf("/\n");
    } else {
        printf("...\n");
    }
}

void printListReverse(Node* tail) {
    Node* curr = tail;
    while (curr != NULL) {
        printf("%d->",curr->num);
        curr = curr->prev;
    }
    printf("/\n");
}

int main() {
    printf("Which type of list do your want to test?\n");
    printf("   0 = NULL-terminated list of size 0 (/)\n");
    printf("   1 = NULL-terminated list of size 1 (0->/)\n");
    printf("   2 = NULL-terminated list of size 2 (0->1->/)\n");
    printf("   3 = NULL-terminated list of size 3 (0->1->2->/)\n");
    printf("   4 = NULL-terminated list of size 4 (0->1->2->3->/)\n");
    printf("   5 = NULL-terminated list of size 5 (0->1->2->3->4->/)\n");
    printf("   6 = cyclic list with 4->0 (0->1->2->3->4->0->1->2->...)\n");
    printf("   7 = cyclic list with 4->1 (0->1->2->3->4->1->2->3->...)\n");
    printf("   8 = cyclic list with 4->2 (0->1->2->3->4->2->3->4->...)\n");
    printf("   9 = cyclic list with 4->3 (0->1->2->3->4->3->4->3->...)\n");
    printf("  10 = cyclic list with 4->4 (0->1->2->3->4->4->4->4->...)\n");
    printf("  11 = cyclic list with 3->0 (0->1->2->3->0->1->2->3->...)\n");
    printf("  12 = cyclic list with 3->1 (0->1->2->3->1->2->3->1->...)\n");
    printf("  13 = cyclic list with 3->2 (0->1->2->3->2->3->2->3->...)\n");
    printf("  14 = cyclic list with 3->3 (0->1->2->3->3->3->3->3->...)\n");
    printf("  15 = cyclic list with 2->0 (0->1->2->0->1->2->0->1->...)\n");
    printf("  16 = cyclic list with 2->1 (0->1->2->1->2->1->2->1->...)\n");
    printf("  17 = cyclic list with 2->2 (0->1->2->2->2->2->2->2->...)\n");
    printf("  18 = cyclic list with 1->0 (0->1->0->1->0->1->0->1->...)\n");
    printf("  19 = cyclic list with 1->1 (0->1->1->1->1->1->1->1->...)\n");
    printf("  20 = cyclic list with 0->0 (0->0->0->0->0->0->0->0->...)\n");
    
    int opt = -1;
    while (opt < 0 || opt > 20) {
        printf("Enter a value between 0 and 20: ");
        scanf("%d",&opt);
        printf("\n");
    }
    
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = (Node*)malloc(sizeof(Node));
    head->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->next->next->next = NULL; //list is NULL-terminated
    head->num = 0;
    head->next->num = 1;
    head->next->next->num = 2;
    head->next->next->next->num = 3;
    head->next->next->next->next->num = 4; // list is 0->1->2->3->4->/

    Node* node0 = head; //backup copy for free later on
    Node* node1 = node0->next; //backup copy for free later on
    Node* node2 = node1->next; //backup copy for free later on
    Node* node3 = node2->next; //backup copy for free later on
    Node* node4 = node3->next; //backup copy for free later on

    switch (opt) {
        case 0: 
            head = NULL; //list is NULL-terminated, size 0
            break;
        case 1: 
            head->next = NULL; //list is NULL-terminated, size 1
            break;
        case 2: 
            head->next->next = NULL; //list is NULL-terminated, size 2
            break;
        case 3: 
            head->next->next->next = NULL; //list is NULL-terminated, size 3
            break;
        case 4: 
            head->next->next->next->next = NULL; //list is NULL-terminated, size 4
            break;
        case 5: 
            head->next->next->next->next->next = NULL; //list is NULL-terminated, size 5
            break;
        case 6: 
            head->next->next->next->next->next = head; //list is cyclic, 0->1->2->3->4->0->1->2->...
            break;
        case 7: 
            head->next->next->next->next->next = head->next; //list is cyclic, 0->1->2->3->4->1->2->3->...
            break;
        case 8: 
            head->next->next->next->next->next = head->next->next; //list is cyclic, 0->1->2->3->4->2->3->4->...
            break;
        case 9: 
            head->next->next->next->next->next = head->next->next->next; //list is cyclic, 0->1->2->3->4->3->4->3->...
            break;
        case 10: 
            head->next->next->next->next->next = head->next->next->next->next; //list is cyclic, 0->1->2->3->4->4->4->4->...
            break;
        case 11: 
            head->next->next->next->next = head; //list is cyclic, 0->1->2->3->0->1->2->...
            break;
        case 12: 
            head->next->next->next->next = head->next; //list is cyclic, 0->1->2->3->1->2->3->...
            break;
        case 13: 
            head->next->next->next->next = head->next->next; //list is cyclic, 0->1->2->3->2->3->...
            break;
        case 14: 
            head->next->next->next->next = head->next->next->next; //list is cyclic, 0->1->2->3->3->3->...
            break;
        case 15: 
            head->next->next->next = head; //list is cyclic, 0->1->2->0->1->2->...
            break;
        case 16: 
            head->next->next->next = head->next; //list is cyclic, 0->1->2->1->2->...
            break;
        case 17: 
            head->next->next->next = head->next->next; //list is cyclic, 0->1->2->2->2->...
            break;
        case 18: 
            head->next->next = head; //list is cyclic, 0->1->0->1->...
            break;
        case 19: 
            head->next->next = head->next; //list is cyclic, 0->1->1->1->...
            break;
        case 20: 
            head->next = head; //list is cyclic, 0->0->0->0->...
            break;
    }

    if (isCyclic(head)) {
        printf("list has a cycle: ");
        printList(head);
    } else {
        printf("list has no cycle: ");
        printList(head);
        Node* tail = convertToDoublyLinkedList(head);
        printf("list in reverse: ");
        printListReverse(tail);
    }

    // properly free-ing heap-malloc'd memory for individual nodes
    free(node0);
    free(node1);
    free(node2);
    free(node3);
    free(node4);

    return 0;
}
