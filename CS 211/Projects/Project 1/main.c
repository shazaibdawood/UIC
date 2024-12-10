//Totalistic Cellular Automaton

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

// convert an integer rule (0-2186) to its base-3 representation, 
// stored in reverse order, as an array of 7 status values, i.e. valArray[7] 
//   ex: rule = 777  -> [0121001], since 777  = 1*3^1 + 2*3^2 + 1*3^3 + 1*3^6   
//   ex: rule = 177  -> [0210200], since 177  = 2*3^1 + 1*3^2 + 2*3^4
//   ex: rule = 2040 -> [0210122], since 2040 = 2*3^1 + 1*3^2 + 1*3^4 + 2*3^5 + 2*3^6
//return true if input rule is valid (0-2186)
//return false if input rule is invalid
bool setValArray(int valArray[7], int rule) {

    if(rule < 0 || rule > 2186){
        return false;
    }
    else{
        for(int i = 0; i < 7; i++){
        valArray[i] = rule % 3;
        rule = rule / 3;
        }

        return true;
    }
}
// reverse the rule array
// void reverseArray(int valArray[7]){
//     int tempArray[7];
//     for(int i = 6; i >= 0; i--){
//         tempArray[i] = valArray[6 - i];
//     }

//     for(int i = 0; i < 7; i++){
//         valArray[i] = tempArray[i];
//     }
// }

// check on number of generations entered
bool setNumGens(int numGenerations){
    if(numGenerations < 1 || numGenerations > 49){
        return false;
    }

    return true;
}

// check on status subitem of the initla middle cell
bool setInitialStatus(int middleCell){
    if(middleCell < 1 || middleCell > 2){
        return false;
    }

    return true;
}

// Print the status of each cell based on the status subitem
void printCells(cell world[WORLD_SIZE]){
    char c;
    for(int i = 0; i < WORLD_SIZE; i++){
        if(world[i].status == 0){
            c = ' ';
        }
        else if(world[i].status == 1){
            c = '-';
        }
        else{
            c = '+';
        }
        printf("%c", c);
        // printf(" %d %d", world[i].localSum, world[i].status);
    }
    
    
}
// Print the count subitem of each cell formatted so that the tens place and ones place are vertical
void printCellCount(cell world[WORLD_SIZE]){
    int countTens[WORLD_SIZE];
    int countOnes[WORLD_SIZE];
    for(int i = 0; i < WORLD_SIZE; i++){
        countTens[i] = world[i].count / 10;
        countOnes[i] = world[i].count % 10;

        if(countTens[i] == 0){
            printf(" ");
        }
        else{
            printf("%d", countTens[i]);
        }
    }
    printf("\n");
    for(int i = 0; i < WORLD_SIZE; i++){
        if(countTens[i] == 0 && countOnes[i] == 0){
            printf(" ");
        }
        else{
            printf("%d", countOnes[i]);
        }
    }
    
    
}

// update the localSum subitem for each cell in the world array based on the
// current statuses for the nearby [left, me, right] cells
// note: world is periodic/cyclic, with front-to-back and back-to-front wrapping 
void setSums(cell world[WORLD_SIZE]) {
    int sum;
    for(int i = 0; i < WORLD_SIZE; i++){
        if(i == 0){
            sum = world[i].status + world[i + 1].status + world[WORLD_SIZE - 1].status;
        }
        else if(i == WORLD_SIZE - 1){
            sum = world[i].status + world[i - 1].status + world[0].status;
        }
        else{
            sum = world[i].status + world[i + 1].status + world[i - 1].status;
        }
        world[i].localSum = sum;
    }

    return;
}

// Evolve the world to the next generation by updating each cell's status value 
// using its localSum subitem (assumed to be updated outside of this function), where
// ruleValArray[7] stores the status values for the 7 possible local sums, in reverse order, 
// e.g. if local sum = 4, the new status value can be found at index 4 of the ruleValArray[].
// This function must also update the count subitems for all cells in world[].
// This function returns the total sum of all status values in world[] after the evolution step.
int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {
    int totalSum = 0;
    for(int i = 0; i < WORLD_SIZE; i++){          
        int statusIndex = world[i].localSum;
        world[i].status = ruleValArray[statusIndex];
        world[i].count += world[i].status;
        totalSum += world[i].status;
    }
    return totalSum;
}


int main() {
    cell world[WORLD_SIZE];
    int ruleArray[7];
    int rule;

    printf("Welcome to the Totalistic Cellular Automaton!\n");

    printf("Enter the rule # (0-2186): ");
    scanf("%d", &rule);
    bool status = setValArray(ruleArray, rule); //Bool reused for the rest of the while loops
    printf("\n");

    while(!status){
        printf("Enter the rule # (0-2186): ");
        scanf("%d", &rule);
        status = setValArray(ruleArray, rule);
        printf("\n");
    }
    printf("\n");
    // reverseArray(ruleArray);

    // array is printed backwards
    printf("The value array for rule #%d is ", rule);
    for(int i = 6; i >= 0; i--){
        printf("%d", ruleArray[i]);
    }
    printf("\n\n");

    printf("The evolution of all possible states are as follows:\n");
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    
    // printed backwards
    printf("New Status: ");
    for(int i = 6; i >= 0; i--){
        char c;
        if(ruleArray[i] == 0){
            c = ' ';
        }
        else if(ruleArray[i] == 1){
            c = '-';
        }
        else{
            c = '+';
        }
        printf("|%c|     ", c);
    }
    printf("\n\n");


    printf("Enter the number of generations (1-49): "); 
    int numGenerations;
    scanf("%d", &numGenerations);
    status = setNumGens(numGenerations);
    printf("\n");

    while(!status){
        printf("Enter the number of generations (1-49): ");
        scanf("%d", &numGenerations);
        status = setNumGens(numGenerations);
        printf("\n");
    }    
    
    printf("Enter the value (1 or 2) for the initial active cell: ");
    int middleCell;
    scanf("%d", &middleCell);
    status = setInitialStatus(middleCell);
    printf("\n");

    while(!status){
        printf("Enter the value (1 or 2) for the initial active cell: ");
        scanf("%d", &middleCell);
        status = setInitialStatus(middleCell);
        printf("\n");
    }    

    printf("\nInitializing world & evolving...\n");
    for(int i = 0; i < WORLD_SIZE; i++){
        world[i].status = 0;
        world[i].count = 0;
        world[i].localSum = 0;
    }
    // count and status are set to the user entered value
    world[(int)WORLD_SIZE / 2].status = middleCell;
    world[(int)WORLD_SIZE / 2].count = middleCell;
    setSums(world); //Update localsums

    printCells(world);
    printf(" %d ", middleCell);
    setSums(world);
    printf("\n");
         
    for(int i = 1; i < numGenerations; i++){
        setSums(world);
        int sum1 = evolveWorld(world, ruleArray);
        printCells(world);
        printf(" %d ", sum1);
        printf("\n");
    }
    printf("_________________________________________________________________");
    printf("\n");
    
    printCellCount(world); 
    
    printf("\n"); // make sure to end your program with a newline

    return 0;
}
