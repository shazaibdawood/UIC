#include <string>
#include <vector>
#include <iostream>
#include "ItemToPurchase.h"
using namespace std;

class ShoppingCart
{
    public:
        ShoppingCart();
        ShoppingCart(string name, string date);
        string GetCustomerName();
        string GetDate();
        void AddItem(const ItemToPurchase &item);
        void RemoveItem(string itemName);
        void ModifyItem(ItemToPurchase &item);
        int GetNumItemsInCart();
        int GetCostOfCart();
        void PrintTotal();
        void PrintDescriptions();

    private:
        string customerName;
        string currentDate;
        vector<ItemToPurchase> cartItems;
};