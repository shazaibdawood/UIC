#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct State_struct {
    char* name;
    char myID[4];
    int population;
    double area;   //units: sq. km
} State;

// separateWords() should search for capital letters 
//  in the input string and add a whitespace before it.
//  Do NOT add a whitespace if the capital letter is at 
//  the beginning of the string OR there is already a 
//  whitespace before it.
//  exs: NewYork -> New York
//       NewYorkCity -> New York City
//       ILoveNewYorkCity -> I Love New York City
//       Chicago, Illinois -> Chicago, Illinois (no change)
void separateWords(char* str) {
    int length = strlen(str);
    char* newStr = (char*) malloc(sizeof(char) * (length * 2));
    char* location = newStr;
    strcpy(newStr, str);
    newStr++;
    str++;
    while(*newStr != '\0'){
        if(isupper(*newStr) && !isspace(*(newStr - 1))){
            *str = ' ';
            str++;
        }
        *str = *newStr;
        newStr++;
        str++;
    }
    *str = '\0';
    
    free(location);
}

// createState() should constuct a single State struct 
//  on the heap. First, allocate space for the State.
//  Then, allocate the name subitem separately, 
//  leaving enough space to store the input stName 
//  twice (i.e. back-to-back), since the string may 
//  grow later. Finally, assign all of the subitems.
//  Return a pointer to the newly created State struct.
State* createState(char* stName, char* stID, int stPop, double stArea) {

    State* newState = (State*) malloc(sizeof(State));
    int length = strlen(stName);
    newState->name = (char*) malloc(sizeof(char) * 2 * length);
    strcpy(newState->name, stName);
    strcpy(newState->myID, stID);
    newState->population = stPop;
    newState->area = stArea;

    return newState; //modify this line
}

void printStats(State* aState) {
    printf("State statistics for %s (%s): \n",aState->name,aState->myID);
    printf("  population = %d people\n",aState->population);
    printf("  area = %0.1lf sq. km \n",aState->area);
    printf("  density = %0.2lf people/sq. km \n",aState->population/aState->area);
}

int main(){
    
    // store and print Illinois's details using a State struct
    State* myState = createState("Illinois","IL",12812508,143793.5);
    printStats(myState);

    // read in another state's details from user input
    char stName[50];
    char stID[4];
    int stPop;
    double stArea;
    printf("\nEnter details for another state... \n");
    printf("  Name: ");
    scanf("%s",stName);
    printf("  ID: ");
    scanf("%s",stID);
    printf("  Population: ");
    scanf("%d",&stPop);
    printf("  Area (sq. km): ");
    scanf("%lf",&stArea);
    printf("\n");
    
    // store the user state's details in another State struct
    State* anotherSt = createState(stName,stID,stPop,stArea);
    // add whitespace between words in the name if necessary
    separateWords(anotherSt->name);
    // print the user state's details 
    printStats(anotherSt);   
    

    //TODO: make sure to free all dynamic heap-allocated memory
    free(anotherSt->name);
    free(anotherSt);
    free(myState->name);
    free(myState);
    

    return 0;
}
