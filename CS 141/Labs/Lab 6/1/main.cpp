// Lab 9: Defining a class


#include <iostream>
using namespace std;

//a class Vacation here
class Vacation{
  private:
  string destination;
  int cost;

  public:
  //write you getters setter here
  void setDestination(string newDestination){
    destination = newDestination;
  }
  
  void setCost(int newCost){
   cost = newCost;
  }
  
  string getDestination(){
    return destination;
  }
  
  int getCost(){
    return cost;
  }
 // write your constructor here
 Vacation(){
    destination = "Alaska";
    cost = 3;
   }
  
 
 bool compare (Vacation newHoliday){
     return (newHoliday.cost == cost && newHoliday.destination == destination);          
  }
 
};


//-----------------------------------------------------------------------------------------------
// *** DO NOT CHANGE ANYTHING BELOW THIS LINE ***
int main()
{

    // Declarations
    Vacation holiday1;
    string destination;
    int cost;
    
    //  ---- Stage 1 ----  Basic class definition, private data members, get() and set() functions
    cout << "Enter the Destination and amount requested: (e.g. MachuPicchu 5): ";
    cin >> destination >> cost ;

    // Test set() member functions
    holiday1.setDestination( destination);
    holiday1.setCost( cost);
    
    // Test get() member functions
      cout <<"   You have requested for  " << holiday1.getCost() << "000$ for"
                           << holiday1.getDestination() 
                           << endl;
  
    // ---- Stage 2 ---- Default constructor
    cout << "2. Using default constructor gives:       ";
    // Invoke the default constructor and display the new Shape
    Vacation holiday2;
    cout <<"   You have requested for  " << holiday2.getCost() << "000$ for"
                           << holiday2.getDestination() 
                           << endl;
                           
    //---- Stage 2 ---- compare two objects
    bool check  = holiday1.compare(holiday2);
    if (check == true){
     cout <<"   You have requested for  " << holiday2.getCost() << "000$ for "
                           << holiday2.getDestination()  <<" before. "
                           << endl;
    }
    else{
       cout <<"   You have not requested for  " << holiday2.getCost() << "000$ for "
                           << holiday2.getDestination()  <<" yet. "
                           << endl;
    }

    return 0;
}//end main()