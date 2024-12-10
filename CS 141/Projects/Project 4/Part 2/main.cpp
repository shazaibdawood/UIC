#include <iostream>
#include <iomanip>
using namespace std;

#include "ShoppingCart.h"
#include "ItemToPurchase.h"

void PrintMenu() {
    cout << "MENU" << endl;
    cout << "a - Add item to cart" << endl;
    cout << "d - Remove item from cart" << endl;
    cout << "c - Change item quantity" << endl;
    cout << "i - Output items' descriptions" << endl;
    cout << "o - Output shopping cart" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    // cout << "Choose an option:" << endl;
}

void ExecuteMenu(char option, ShoppingCart& theCart) {
    if(option == 'o')
    {
        cout << "OUTPUT SHOPPING CART" << endl;
        cout << theCart.GetCustomerName() << "'s Shopping Cart - " << theCart.GetDate() << endl;
        cout << "Number of Items: " << theCart.GetNumItemsInCart() << endl;
        cout << endl;
        
        theCart.PrintTotal();

        // cout << endl;
        // PrintMenu();
    }
    else if(option == 'i')
    {
        cout << "OUTPUT ITEMS' DESCRIPTIONS" << endl;
        cout << theCart.GetCustomerName() << "'s Shopping Cart - " << theCart.GetDate() << endl;
        cout << endl;
        cout << "Item Descriptions" << endl;
        theCart.PrintDescriptions();

        // cout << endl;
        // PrintMenu();
    }
    else if(option == 'a')
    {
        ItemToPurchase newItem;
        string name;
        string description;
        int price;
        int quantity;

        cin.ignore();
        cout << "ADD ITEM TO CART" << endl;
        cout << "Enter the item name:" << endl;
        getline(cin , name);
        cout << "Enter the item description:" << endl;
        getline(cin, description);
        cout << "Enter the item price:" << endl;
        cin >> price;
        cout << "Enter the item quantity:" << endl;
        cin >> quantity;

        newItem.SetName(name);
        newItem.SetPrice(price);
        newItem.SetQuantity(quantity);
        newItem.SetDescription(description);

        theCart.AddItem(newItem);
        
        // cout << endl;
        // PrintMenu();
    }
    else if(option == 'd')
    {
        string name;
        cout << "REMOVE ITEM FROM CART" << endl; 

        cout << "Enter name of item to remove:" << endl;
        cin.ignore();
        getline(cin, name);

        theCart.RemoveItem(name);

        // cout << endl;
        // PrintMenu();
    }
    else if(option == 'c')
    {
        string name;
        int quantity;
        cout << "CHANGE ITEM QUANTITY" << endl;

        cout << "Enter the item name:" << endl;
        cin.ignore();
        getline(cin, name);

        ItemToPurchase newItem;
        newItem.SetName(name);

        theCart.ModifyItem(newItem);

        // cout << endl;
        // PrintMenu();
    }
    else
    {
        cout << "Choose an option:" << endl;
    }
   
}

int main() {
   string name;
   string date;

   cout << "Enter customer's name:" << endl;
   getline(cin, name);

   cout << "Enter today's date:" << endl;
   getline(cin, date);

   ShoppingCart myCart(name, date);
   
   cout << endl;
   cout << "Customer name: " << name << endl;
   cout << "Today's date: " << date << endl;

    cout << endl;
    PrintMenu();
    cout << "Choose an option:" << endl;

    char userChoice;
    cin >> userChoice;

    while(userChoice != 'q')
    {
        ExecuteMenu(userChoice, myCart);

        if(userChoice == 'a' || userChoice == 'd' || userChoice == 'c' || userChoice == 'i' || userChoice == 'o')
        {
            cout << endl;
            PrintMenu();
            cout << "Choose an option:" << endl;
        }
        
        cin >> userChoice;
    }

   return 0;
}