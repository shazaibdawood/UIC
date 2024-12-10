#include <iostream>
#include <vector> 
using namespace std;

void GetUserValues(vector<int>& userValues, int numValues)
{
   for(int i = 0; i < numValues; i++)
   {
      int temp;
      cin >> temp;
      
      userValues.push_back(temp);
   }
}

void IntsLessThanOrEqualToThreshold(vector<int> userValues, int upperThreshold, vector<int>& resValues)
{
   for(unsigned int i = 0; i < userValues.size(); i++)
   {
      if(userValues.at(i) <= upperThreshold)
      {
         resValues.push_back(userValues.at(i));
      }
   }
}

int main() {
   vector<int> userValues; 
   vector<int> resValues; 
   int upperThreshold;
   int numValues;
   unsigned int i;
   
   cin >> numValues;
   GetUserValues(userValues, numValues);

   cin >> upperThreshold;
   IntsLessThanOrEqualToThreshold(userValues, upperThreshold, resValues);
   for (i = 0; i < resValues.size(); ++i) {
      cout << resValues.at(i) << " ";
   }
   cout << endl;
   
   return 0;
}
