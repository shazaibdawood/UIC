#include <iostream>
#include <vector>   // Must include vector library to use vectors
using namespace std;

int main() {
   vector<int> userInts; // A vector to hold the user's input integers
   
   int vSize;
   
   cin >> vSize;
   
   for(int i = 0; i < vSize; i++)
   {
      int temp;
      
      cin >> temp;
      
      userInts.push_back(temp);
   }
   
   for(int i = vSize - 1; i >= 0; i--)
   {
      cout << userInts.at(i) << ",";
   }
   cout << endl;

   return 0;
}