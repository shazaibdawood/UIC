#include <iostream>
using namespace std;

#include "ItemToPurchase.h"

int main() {
   string name;
   int price;
   int quantity;

   cout << "Item 1" << endl;
   cout << "Enter the item name:" << endl;
   getline(cin, name);
   cout << "Enter the item price:" << endl;
   cin >> price;
   cout << "Enter the item quantity:" << endl;
   cin >> quantity;

   ItemToPurchase item1;
   item1.SetName(name);
   item1.SetPrice(price);
   item1.SetQuantity(quantity);

   cin.ignore();
   cout << endl;

   cout << "Item 2" << endl;
   cout << "Enter the item name:" << endl;
   getline(cin, name);
   cout << "Enter the item price:" << endl;
   cin >> price;
   cout << "Enter the item quantity:" << endl;
   cin >> quantity;

   ItemToPurchase item2;
   item2.SetName(name);
   item2.SetPrice(price);
   item2.SetQuantity(quantity);

   cout << endl;
    cout << "TOTAL COST" << endl;
    int total = 0;

    name = item1.GetName();
    price = item1.GetPrice();
    quantity = item1.GetQuantity();

    cout << name << " " << quantity << " @ $" << price << " = $" << (quantity * price) << endl;
    total += (quantity * price);

    name = item2.GetName();
    price = item2.GetPrice();
    quantity = item2.GetQuantity();

    cout << name << " " << quantity << " @ $" << price << " = $" << (quantity * price) << endl;
    total += (quantity * price);

    cout << endl;
    cout << "Total: $" << total << endl;

   return 0;
}