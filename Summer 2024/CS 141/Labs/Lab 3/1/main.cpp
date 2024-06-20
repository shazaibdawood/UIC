#include <iostream>
using namespace std;

int CalcNumCharacters(string userString, char userChar)
{
   int count = 0;
   for(int i = 0; i < userString.size(); i++)
   {
      if(userString.at(i) == userChar)
      {
         count++;
      }
   }
   
   return count;
}

int main() {
   string userString;
   char userChar;
    
   cin >> userChar;
   getline(cin, userString);
   
   int count = CalcNumCharacters(userString, userChar);
   
   if(count > 1)
   {
      cout << count << " " << userChar << "'s" << endl;
   }
   else
   {
      cout << count << " " << userChar << endl;
   }

   return 0;
}