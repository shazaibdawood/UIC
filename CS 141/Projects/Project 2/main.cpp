#include <iostream>
#include <vector>
using namespace std;

void getRoster(vector<int>& jerseys, vector<int>& ratings)
{
    int jNumber, rating;

    for(int i = 1; i <= 5; i++)
   {
        cout << "Enter player " << i << "'s jersey number:" << endl;
        cin >> jNumber;
        jerseys.at(i - 1) = jNumber;

        cout << "Enter player " << i << "'s rating:" << endl;
        cin >> rating;
        ratings.at(i - 1) = rating;

        cout << endl;
   }
}

void printRoster(vector<int>& jerseys, vector<int>& ratings)
{
   cout << "ROSTER" << endl;
   for(int i = 0; i < jerseys.size(); i++)
   {
        cout << "Player " << (i + 1) << " -- Jersey number: " << jerseys.at(i) 
        << ", Rating: " << ratings.at(i) << endl;
   }
   cout << endl;
}

char printMenu()
{
    char userChoice;

    cout << "MENU" << endl;
    cout << "a - Add player" << endl;
    cout << "d - Remove player" << endl;
    cout << "u - Update player rating" << endl;
    cout << "r - Output players above a rating" << endl;
    cout << "o - Output roster" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;

    cin >> userChoice;
    return userChoice;
}

void addPlayer(vector<int>& jerseys, vector<int>& ratings)
{
    int jNumber, rating;

    cout << "Enter a new player's jersey number:" << endl;
    cin >> jNumber;
    jerseys.push_back(jNumber);

    cout << "Enter the player's rating:" << endl;
    cin >> rating;
    ratings.push_back(rating);

    cout << endl;
}

void updatePlayerRating(vector<int>& jerseys, vector<int>& ratings)
{
    int jNumber, rating, changeIndex;

    cout << "Enter a jersey number:" << endl;
    cin >> jNumber;

    for(int i = 0; i < jerseys.size(); i++)
    {
        if(jerseys.at(i) == jNumber)
        {
            changeIndex = i;
            break;
        }
    }

    cout << "Enter a new rating for player:" << endl;
    cin >> rating;

    ratings.at(changeIndex) = rating;
}

void deletePlayer(vector<int>& jerseys, vector<int>& ratings)
{
    int jNumber, rating, deleteIndex;

    cout << "Enter a jersey number:" << endl;
    cin >> jNumber;

    for(int i = 0; i < jerseys.size(); i++)
    {
        if(jerseys.at(i) == jNumber)
        {
            deleteIndex = i;
            break;
        }
    }

    jerseys.erase(jerseys.begin() + deleteIndex);
    ratings.erase(ratings.begin() + deleteIndex);
}

void printByRating(vector<int>& jerseys, vector<int>& ratings)
{
    int threshold;

    cout << "Enter a rating:" << endl;
    cin >> threshold;

    cout << endl;
    cout << "ABOVE " << threshold << endl;

    for(int i = 0; i < ratings.size(); i++)
    {
        if(ratings.at(i) > threshold)
        {
            cout << "Player " << (i + 1) << " -- Jersey number: " << jerseys.at(i) 
            << ", Rating: " << ratings.at(i) << endl;
        }
    }
    cout << endl;
}

int main() {

   vector <int> jerseys(5);
   vector <int> ratings(5);
   char userChoice;

   getRoster(jerseys, ratings);

   printRoster(jerseys, ratings);

   userChoice = printMenu();

   while(userChoice != 'q')
   {
        if(userChoice == 'o')
        {
            printRoster(jerseys, ratings);
        }
        else if(userChoice == 'a')
        {
            addPlayer(jerseys, ratings);
        }
        else if(userChoice == 'u')
        {
            updatePlayerRating(jerseys, ratings);
        }
        else if(userChoice == 'd')
        {
            deletePlayer(jerseys, ratings);
        }
        else if(userChoice == 'r')
        {
            printByRating(jerseys , ratings);
        }

        userChoice = printMenu();
   }

   return 0;
}