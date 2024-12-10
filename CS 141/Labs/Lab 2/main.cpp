#include <iostream>
using namespace std;

int main() {

    int totalChange;

   cin >> totalChange;

   if(totalChange <= 0)
   {
        cout << "No change" << endl;
   }
   else
   {
        int dollars, quarters, dimes, nickels, pennies;

        dollars = totalChange / 100;
        totalChange = totalChange % 100;

        quarters = totalChange / 25;
        totalChange = totalChange %25;

        dimes = totalChange / 10;
        totalChange = totalChange % 10;

        nickels = totalChange / 5;
        totalChange = totalChange % 5;

        pennies = totalChange;

        if(dollars == 1)
        {
            cout << dollars << " Dollar" << endl;
        }
        else if(dollars > 1)
        {
            cout << dollars << " Dollars" << endl;
        }

        if(quarters == 1)
        {
            cout << quarters << " Quarter" << endl;
        }
        else if(quarters > 1)
        {
            cout << quarters << " Quarters" << endl;
        }

        if(dimes == 1)
        {
            cout << dimes << " Dime" << endl;
        }
        else if(dimes > 1)
        {
            cout << dimes << " Dimes" << endl;
        }

        if(nickels == 1)
        {
            cout << nickels << " Nickel" << endl;
        }
        else if(nickels > 1)
        {
            cout << nickels << " Nickels" << endl;
        }

        if(pennies == 1)
        {
            cout << pennies << " Penny" << endl;
        }
        else if(pennies > 1)
        {
            cout << pennies << " Pennies" << endl;
        }
   }

   return 0;
}