#include <iostream>
using namespace std;

int main() {
   const int ROCK = 0;
   const int PAPER = 1;
   const int SCISSORS = 2;

   int seed;
   cin >> seed;
   srand(seed);

   string player1;
   string player2;
   int numRounds;

   cin >> player1 >> player2 >> numRounds;

   while(numRounds < 1)
   {
    cout << "Rounds must be > 0" << endl;
    cin >> numRounds;
   }

   cout << player1 << " vs " << player2 << " for " << numRounds << " rounds" << endl;

   int p1Wins = 0;
   int p2Wins = 0;

    for(int i = 0; i < numRounds; i++)
    {
        int rand1 = rand() % 3;
    int rand2 = rand() % 3;

    while(rand1 == rand2)
    {
        cout << "Tie" << endl;

        rand1 = rand() % 3;
        rand2 = rand() % 3;
    }

    if((rand1 == 0 && rand2 == 2) || (rand1 == 1 && rand2 == 0) || (rand1 == 2 && rand2 == 1))
    {
        p1Wins++;
        cout << player1 << " wins with ";
        
        if(rand1 == 0)
        {
            cout << "rock";
        }
        else if(rand1 == 1)
        {
            cout << "paper";
        }
        else
        {
            cout << "scissors";
        }

        cout << endl;
    }
    else
    {
        p2Wins++;
        cout << player2 << " wins with ";
        
        if(rand2 == 0)
        {
            cout << "rock";
        }
        else if(rand2 == 1)
        {
            cout << "paper";
        }
        else
        {
            cout << "scissors";
        }

        cout << endl;
    }
        }
    
    cout << player1 << " wins " << p1Wins << " and " << player2 << " wins " << p2Wins << endl;

   return 0;

}
