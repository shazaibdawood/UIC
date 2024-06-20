#include <iostream>

using namespace std;

// Test - 1
// PrintNumPattern(12, 3);
// First pass:
// x = 12
// y = 3
// temp = 9
// Condition: false
// print - 12 [12](Printed at the end)

// Second pass:
// x = 9
// y = 3
// temp = 6
// Condition: false
// print - 12 9 [9 12]

// Third pass:
// x = 6
// y = 3
// temp = 3
// Condition: false
// print - 12 9 6 [6 9 12]

// Fourth pass:
// x = 3
// y = 3
// temp = 0
// Condition: false
// print - 12 9 6 3 [3 6 9 12]

// Fifth pass:
// x = 0
// y = 3
// temp = -3
// Condition: false
// print - 12 9 6 3 0 [0 3 6 9 12]

// Sixth pass:
// x = -3
// y = 3
// temp = -6
// Condition: true
// print - 12 9 6 3 0 -3 0 3 6 9 12

void PrintNumPattern(int x, int y)
{
    int temp = x - y;

    cout << x << " ";

    if(x < 0)
    {
        return;
    }
    else
    {
        PrintNumPattern(temp, y);
        cout << x << " ";
    }
}

int main() {
   int num1;
   int num2;

   cin >> num1;
   cin >> num2;
   PrintNumPattern(num1, num2);
   
   return 0;
}