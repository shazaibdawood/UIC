#include <iostream>

#include "VendingMachine.h"
using namespace std;

int main() {
	VendingMachine myMachine;
    int numDrinks, numRestock;

    cin >> numDrinks;
    cin >> numRestock;

    myMachine.Purchase(numDrinks);
    myMachine.Restock(numRestock);
    myMachine.Report();
}