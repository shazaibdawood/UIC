#include <iostream>
using namespace std;

int greatestCommonDivisor(int a, int b)
{
   if(a % b == 0)
   {
      return b;
   }

   return greatestCommonDivisor(b, a % b);
}

bool diophantine(int a, int b, int c, int &x, int &y)
{
   if(c % greatestCommonDivisor(a, b) != 0)
   {
      return false;
   }
   else if(a % b == 0)
   {
      x = 0;
      y = c / b;
      return true;
   }
   else
   {
      int q = a / b;
      int r = a % b;
      int u = y + (q * x);
      int v = x;
      
      if(diophantine(b, r, c, u, v))
      {
         x = v;
         y = u - (q * x);
      }
      return true;
   }
}

int main() {

    int a, b, c, x, y;

    cout << "Enter a b c" << endl;
    cin >> a >> b >> c;
    cout << endl;

    cout << "Result: ";
    if (diophantine(a, b, c, x, y)) {
       cout << x << " " << y << endl;
    } else {
       cout << "No solution!" << endl;
    }
   
   return 0;
}