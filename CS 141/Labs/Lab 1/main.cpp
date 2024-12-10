#include <iostream>
using namespace std;

int main() {
   long long phoneNumber;

   cin >> phoneNumber;
   
   int areaCode, prefix, lineNum;
   
   lineNum = phoneNumber % 10000;
   phoneNumber /= 10000;
   
   prefix = phoneNumber % 1000;
   phoneNumber /= 1000;
   
   areaCode = phoneNumber;
   
   cout << "(" << areaCode << ") " << prefix << "-" << lineNum << endl;
   
   return 0;
}