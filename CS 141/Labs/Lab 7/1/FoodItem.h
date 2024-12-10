#ifndef FOODITEMH
#define FOODITEMH

#include <string>

using namespace std;

class FoodItem {
   public:
      // TODO: Declare default constructor
      FoodItem();
      FoodItem(string, double, double, double);

      // TODO: Declare second constructor with parameters
      // to initialize private data members

      string GetName();

      double GetFat();

      double GetCarbs();

      double GetProtein();

      double GetCalories(double numServings);

      void PrintInfo();

   private:
      string name;
      double fat;
      double carbs;
      double protein;
};

#endif