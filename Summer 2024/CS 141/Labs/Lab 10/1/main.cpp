#include <iostream>
using namespace std;

class Node
{
   public:
      int data;
      Node *pNext;
};


// Option 1: Display the list number
void displayNumberValues( Node *pHead)
{
    while( pHead != NULL) {
        cout << pHead->data << " ";
        pHead = pHead->pNext;
    }
    cout << endl;
}


// Option 2: Find and return the max of all list numbers
int getMaxOfAllNumbers( Node* pHead)
{
   Node *pCurrent = pHead;
   int max = pCurrent->data;
   
   while(pCurrent != NULL)
   {
      if(pCurrent->data > max)
      {
         max = pCurrent->data;
      }
      pCurrent = pCurrent->pNext;
   }
   
   return max;
}


// Option 3: Given three nodes delete the middle node and return the data
//           stored in it.
//           __________        ----------       ----------
//           |   |    | -----> |    |   |-----> |    |   |
//           | 1 |    |        | 2  |   |       | 3  |   |
//           ----------        ----------       ----------
//           
//                    Eg.   Delete the middle node
int deleteSecondNode( Node* pHead)
{
   Node* second = pHead->pNext;
   int secondData = second->data;
   
   pHead->pNext = second->pNext;
   
   return secondData;
}


//-----------------------------------------------------------------------
//       *** Do not change anything below this point. ***
//------------------------------------------------------------------------

int main()
{
   int userInput;
   Node *pHead = NULL;
   Node *pTemp;
   
   cout<<"Enter list numbers separated by space, followed by -1: ";
   cin >> userInput;
   // Keep looping and prepending nodes on the list until end-of-input flag of -1 is given
   while( userInput != -1) {
      // Store this number on the list
       pTemp = new Node;
       pTemp->data = userInput;
       pTemp->pNext = pHead;
       pHead = pTemp;
       cin >> userInput;
   }
   // stage 1
   cout << endl << "The list number values are: ";
   displayNumberValues( pHead);       // This function is already provided
   
   // //stage 2
   // cout << endl << "The max of all numbers on the list is: "
   //                   << getMaxOfAllNumbers( pHead)    // *** You must write this function
   //                   << endl;
   // // //stage 3            
   // cout << endl << "Deleting second node. " << endl;
   // int data = deleteSecondNode( pHead);           // *** You must write this function
   // cout<<"The data of the second node is: "<<data;
   // cout << endl << "The list number values are: ";
   // displayNumberValues(pHead);
    
   return 0;
}//end main()