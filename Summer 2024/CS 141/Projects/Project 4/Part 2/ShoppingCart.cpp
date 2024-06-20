#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "ShoppingCart.h"

ShoppingCart::ShoppingCart()
{
    customerName = "none";
    currentDate = "January 1, 2016";
}

ShoppingCart::ShoppingCart(string name, string date)
{
    customerName = name;
    currentDate = date;
}

string ShoppingCart::GetCustomerName()
{
    return customerName;
}

string ShoppingCart::GetDate()
{
    return currentDate;
}

void ShoppingCart::AddItem(const ItemToPurchase &item)
{
    cartItems.push_back(item);
}

void ShoppingCart::RemoveItem(string itemName)
{
    for(int i = 0; i < cartItems.size(); i++)
    {
        string searchName = cartItems.at(i).GetName();
        if(searchName == itemName)
        {
            cartItems.erase(cartItems.begin() + i);
            return;
        }
    }
    cout << "Item not found in cart. Nothing removed." << endl;
}

void ShoppingCart::ModifyItem(ItemToPurchase &item)
{
    string itemName = item.GetName();
    cout << "Enter the new quantity:" << endl;
    int itemQuantity;
    cin >> itemQuantity;
    
    for(int i = 0; i < cartItems.size(); i++)
        {
            string searchName = cartItems.at(i).GetName();
            if(searchName == itemName)
            {
                // string itemDescription = item.GetDescription();
                // int itemPrice = item.GetPrice();
                // int itemQuantity = item.GetQuantity();
                // if(itemDescription == "none")
                // {   
                //     getline(cin, itemDescription);
                //     item.SetDescription(itemDescription);
                // }
                // if(itemPrice == 0)
                // {
                //     cin >> itemPrice;
                //     item.SetPrice(itemPrice);
                // }
                // if(itemQuantity == 0)
                // {
                //     cout << "Enter the new quantity:" << endl;
                //     cin >> itemQuantity;
                //     item.SetQuantity(itemQuantity);
                // }

                cartItems.at(i).SetQuantity(itemQuantity);
                return;
            }
        }
        cout << "Item not found in cart. Nothing modified." << endl;
}
int ShoppingCart::GetNumItemsInCart()
{
    int numItems = 0;

    for(int i = 0; i < cartItems.size(); i++)
    {
        numItems += cartItems.at(i).GetQuantity();
    }

    return numItems;
}
int ShoppingCart::GetCostOfCart()
{
    int total = 0;
    for(int i = 0; i < cartItems.size(); i++)
    {
        int totalprice = cartItems.at(i).GetPrice() * cartItems.at(i).GetQuantity();
        total += totalprice;
    }
    return total;
}
void ShoppingCart::PrintTotal()
{
    if(cartItems.size() == 0)
    {
        cout << "SHOPPING CART IS EMPTY" << endl;
    }
    else
    {
        for(int i = 0; i < cartItems.size(); i++)
        {
            cartItems.at(i).PrintItemCost();
        }
    }
    cout << endl;
    cout << "Total: $" << GetCostOfCart() << endl;
}
void ShoppingCart::PrintDescriptions()
{
    if(cartItems.size() == 0)
    {
        cout << "SHOPPING CART IS EMPTY" << endl;
    }
    else
    {
        for(int i = 0; i < cartItems.size(); i++)
        {
            cartItems.at(i).PrintItemDescription();
        }
    }
}