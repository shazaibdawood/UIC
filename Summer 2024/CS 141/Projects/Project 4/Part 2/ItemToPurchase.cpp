#include <iostream>
using namespace std;

#include "ItemToPurchase.h"

ItemToPurchase::ItemToPurchase()
{
    itemName = "none";
    itemPrice = 0;
    itemQuantity = 0;
    itemDescription = "none";
}

ItemToPurchase::ItemToPurchase(string name, string description, int price, int quantity)
{
    itemName = name;
    itemDescription = description;
    itemPrice = price;
    itemQuantity = quantity;
}

void ItemToPurchase::SetName(string name)
{
    itemName = name;
}

string ItemToPurchase::GetName() const
{
    return itemName;
}

void ItemToPurchase::SetPrice(int price)
{
    itemPrice = price;
}

int ItemToPurchase::GetPrice() const
{
    return itemPrice;
}

void ItemToPurchase::SetQuantity(int quantity)
{
    itemQuantity = quantity;
}

int ItemToPurchase::GetQuantity() const
{
    return itemQuantity;
}

void ItemToPurchase::SetDescription(string description)
{
    itemDescription = description;
}

string ItemToPurchase::GetDescription() const
{
    return itemDescription;
}

void ItemToPurchase::PrintItemCost()
{
    cout << itemName << " " << itemQuantity << " @ $" << itemPrice << " = $" << (itemQuantity * itemPrice) << endl;
}

void ItemToPurchase::PrintItemDescription()
{
    cout << itemName << ": " << itemDescription << endl;
}