#include <iostream>
using namespace std;

// Global constant
const int LineLength = 81;

// Create the function declarations so the code works. 
// For each function you implement, uncomment the driver code within main 
// so you can test it.
int myStrlen(char x[])
{
   int i = 0;
   while(x[i] != '\0')
   {
      i++;
   }
   return i;
}

void removeVowels(char y[], char x[])
{
   int i = 0;
   int j = 0;
   while(x[i] != '\0')
   {
      if(x[i] != 'a' && x[i] != 'e' && x[i] != 'i' && x[i] != 'o' && x[i] != 'u')
      {
         y[j] = x[i];
         j++;
      }
      i++;
   }
}

void duplicateString(char y[], int num)
{
   int len = myStrlen(y);
   int newLen = len * num;
   string origString, newString;
   
   for(int i = 0; i < len; i++)
   {
      origString += y[i];
   }
   
   for(int i = 0; i < num; i++)
   {
      newString += origString;
   }
   for(int i = 0; i < newLen; i++)
   {
      y[i] = newString[i];
   }
   for(int i = newLen; i < LineLength; i++)
   {
      y[i] = '\0';
   }
}

int main()
{
   char userInput[LineLength];
   char newString[LineLength];
   
   // Initialize newString to have all NULL characters
   // Remember all C strings end with a NULL characters,
   //    taking this step helps us avoid forgetting to 
   //    terminate the C string with a NULL character
   for( int i=0; i < LineLength; i++) 
   {
      newString[i] = '\0';    // Set to the NULL character
   } 

   // Get user input
   cout << "Enter a word: ";
   cin >> userInput;

   // Display results from functions.
   // If userInput is "cat", then the line below would give a length of 3
   cout << "That word has length: " << myStrlen(userInput) << endl;

   // Remove vowels, putting resulting new string into array newString
   // For instance removing vowels from "cat" would put "ct" into newString.
   removeVowels(newString, userInput);
   cout << userInput << " without vowels is: " << newString << endl;

   // Duplicate the current contents of newString some number of times.
   // If 3 duplicates are chosen and newString is currently "ct", then 
   // newString would become "ctctct"
   int howManyTotal = 0;
   cout << "Enter how many duplicates to make: ";
   cin >> howManyTotal;
   duplicateString(newString, howManyTotal);
   cout << newString << endl;

   return 0;
}