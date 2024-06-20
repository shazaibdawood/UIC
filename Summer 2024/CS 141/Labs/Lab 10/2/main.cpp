#include <iostream>
using namespace std;
 

class Node {
   public:
         int data;
         Node *pNext;
};




void displayNumberValues( Node *pHead)
{
    while( pHead != NULL) {
        cout << pHead->data << " ";
        pHead = pHead->pNext;
    }
    cout << endl;
}



//Option 1: Search the list
// TODO: complete the function below to search for a given value in linked lsit
// return true if value exists in the list, return false otherwise.

bool  linkedlistSearch( int value, Node* pHead)
{
   Node* pCurrent = pHead;
   
   while(pCurrent != NULL)
   {
      if(pCurrent->data == value)
      {
         return true;
      }
      
      pCurrent = pCurrent->pNext;
   }
   return false;
}


//Option 2: get sum of all values
// TODO: complete the function below to return the sum of all elements in the linked list.

int getSumOfAllNumbers( Node* pHead)
{
   int sum = 0;
   Node* pCurrent = pHead;
   
   while(pCurrent != NULL)
   {
      sum += pCurrent->data;
      pCurrent = pCurrent->pNext;
   }
   
   return sum;
}



int main()
{
   int userInput;
   Node *pHead = NULL;
   Node *pTemp;
     
   cout<<"Enter list numbers separated by space, followed by -1: ";  
   cin >> userInput;
     
   // Keep looping until end of input flag of -1 is given
   while( userInput != -1) {
      // Store this number on the list
      pTemp = new Node;
      pTemp->data = userInput;
      pTemp->pNext = pHead;
      pHead = pTemp;
         
      cin >> userInput;
   }
   
   cout <<" Menu options:\n";
   cout <<" 1. Search for a value.  \n"
        <<" 2. Display the sum of all numbers on the list.  \n"
        <<" 3. Exit program. \n";
   
   cin >> userInput;
   cout<<"Your choice ->" << userInput <<endl; 
   
   switch(userInput){
      
      case(1):
         int num; 
         cout<<"Enter a value to initiate a search:"<<endl;
         cin >> num; 
         if(linkedlistSearch(num, pHead))
         {
            cout << "The number you entered exists in this list." << endl;
         }
         else
         {
            cout << "The number you entered does not exist in this list." << endl;
         }
         break;
      case(2):
         cout << "The sum of all numbers on the list is: " << getSumOfAllNumbers(pHead) << endl;
         break;
      case(3):
         exit(0);
           }
   
      
   return 0;
}