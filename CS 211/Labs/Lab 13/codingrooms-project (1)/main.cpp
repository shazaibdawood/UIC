#include "Plant.h"
#include "Flower.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// TODO: Define a PrintVector function that prints an vector of plant (or flower) object pointers

void PrintVector(const vector<Plant*>& myGarden){
    for(int i = 0; i <myGarden.size(); i++){
        cout << "Plant " << i + 1 << " Information:" << endl;
        myGarden.at(i)->PrintInfo();
        cout << endl;
    }
}

int main() {
   // TODO: Declare a vector called myGarden that can hold object of type plant pointer
   vector<Plant*> myGarden;

   // TODO: Declare variables - plantName, plantCost, flowerName, flowerCost,
   //       colorOfFlowers, isAnnual
   string input;

   cin >> input;

   while(input != "-1") {
   // TODO: Check if input is a plant or flower
   //       Store as a plant object or flower object
   //       Add to the vector myGarden
      
      if(input == "plant"){
        string plantName;
        int plantCost;
        cin >> plantName >> plantCost;

        Plant* newPlant = new Plant();
        newPlant->SetPlantName(plantName);
        newPlant->SetPlantCost(plantCost);
        myGarden.push_back(newPlant);
      }
      else if(input == "flower"){
        string flowerName, colorOfFlowers;
        int flowerCost;
        string isAnnual;

        cin >> flowerName >> flowerCost >> isAnnual >> colorOfFlowers;

        Flower* newFlower = new Flower();
        newFlower->SetPlantName(flowerName);
        newFlower->SetPlantCost(flowerCost);
        // newFlower->SetPlantType(isAnnual);
        newFlower->SetColorOfFlowers(colorOfFlowers);

        if(isAnnual == "true"){
            newFlower->SetPlantType(true);
        }
        else if(isAnnual == "false"){
            newFlower->SetPlantType(false);
        }

        myGarden.push_back(newFlower);
      }
      cin >> input;
   }

   // TODO: Call the method PrintVector to print myGarden

   PrintVector(myGarden);

   for (size_t i = 0; i < myGarden.size(); ++i) {
      delete myGarden.at(i);
   }
   
   return 0;
}