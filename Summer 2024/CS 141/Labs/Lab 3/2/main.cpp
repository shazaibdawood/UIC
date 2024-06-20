#include <iostream>
using namespace std;

int Fibonacci(int n)
{
   if(n >= 0)
   {
      int first = 0;
      int second = 1;
      int next;
      
      for(int i = 0; i <= n; i++)
      {
         if(i == 0)
         {
            next = 0;
            continue;
         }
         else if(i == 1)
         {
            next = 1;
            continue;
         }
         
         next = first + second;
         
         first = second;
         second = next;
      }
      
      return next;
   }
   else
   {
      return -1;
   }
}

int main() {
   int startNum;
      
   cin >> startNum;
   cout << "Fibonacci(" << startNum << ") is " << Fibonacci(startNum) << endl;

   return 0;
}