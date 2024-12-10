#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change constant kYourNetID to store your netID 
 *    - your submission will be manually inspected to ensure
 *      you have used the exact string that is your netID
 *    - thus, it is vital you understand what your netID is
 *    - ex: Professor Reckinger's email is scotreck@uic.edu, so
 *          Professor Reckinger's netID is scotreck     
 *    - ex: Professor Kidane's email is ekidan2@uic.edu, so
 *          Professor Kidane's netID is ekidan2     
 *    - ex: Student Sparky's email is sspark211@uic.edu, so
 *          Student Sparky's netID is sspark211 
 * WARNING: Once you've set set this constant and started 
 * exploring your maze, do NOT edit the value of kYourNetID. 
 * Changing kYourNetID will change which maze you get back, 
 * which might invalidate all your hard work!
 */
const string kYourNetID = "sdawo2";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "ESSSEENNNW";
const string kPathOutOfTwistyMaze = "ESENWESE";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    set<string> completeItems = {"Spellbook", "Wand", "Potion"};
    set<string> collectedItems;

    if(start->whatsHere != ""){
        collectedItems.insert(start->whatsHere);
    }

    for(char step : moves){
        if(step == 'N'){
            start = start->north;
        }
        else if(step == 'E'){
            start = start->east;
        }
        else if(step == 'W'){
            start = start->west;
        }
        else if(step == 'S'){
            start = start->south;
        }
        else{
            return false;
        }

        if(start == nullptr){
            return false;
        }

        if(start->whatsHere != ""){
            collectedItems.insert(start->whatsHere);
        }
    }
    
    if(start == nullptr){
        return false;
    }

    if(start->whatsHere != ""){
        collectedItems.insert(start->whatsHere);
    }

    return (collectedItems.size() == 3);
}
