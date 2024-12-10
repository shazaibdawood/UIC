// Shazaib Dawood
// CS 211 4PM Fall 2024 UIC
// Creating and updating a food web using dynamic arrays

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// using namespace std;

typedef struct Org_struct {
    char name[20];
    int* prey; //dynamic array of indices  
    int numPrey;
} Org;


void addOrgToWeb(Org** ppWeb, int* pNumOrg, char* newOrgName) {
    
    // TODO (Task 3): add a new organism to the food web.
    //      Inputs: 
    //          ppWeb - a pointer to a dynamically allocated array of Orgs; i.e. a pointer to a pointer
    //          pNumOrg - a passed-by-pointer parameter for the number of organisms = size of web[]
    //          newOrgName - a character array (i.e. string) for the name of the new organism 
    //      Outputs:
    //          ppWeb - the Org array must be reallocated on the heap to allow space for the new organism
    //          pNumOrg - the number of organisms should increase by one to account for the new organism
    //        
    //      Note...
    //      (1) web may be an empty Org array if there are no organisms in the food web yet; 
    //          in this case, the input *ppWeb should be NULL;
    //      (2) otherwise, a new heap allocation must be made to store all the Orgs in the web 
    //          PLUS one additional Org space for the new organism; this reallocation step must 
    //          be done with only a call to malloc (i.e. not realloc()); make sure to free the 
    //          memory associated with the original web once the Orgs have been copied over to 
    //          the new memory allocation;
    //      (3) the string copy function must be used to copy newOrgName to the web
    //          ex: strcpy((*ppWeb)[0].name, newOrgName) // copies newOrgName to the name subitem of the Org at index 0
    //      (4) set default initial values for the prey subitem and numPrey for the new Org.
    //      (5) append the new organism to the back of the pWeb array.
    
    // Make a new food web with an extra spot
    // Copy all current elements into new food web
    // free the old web
    // add the new organism into the new food web
    // set the old web equal tot he new web
    Org* newWeb = (Org*) malloc(sizeof(Org) * (*pNumOrg + 1));

    for(int i = 0; i < *pNumOrg; i++){
        newWeb[i] = (*ppWeb)[i];
    }

    free(*ppWeb);
    strcpy(newWeb[*pNumOrg].name, newOrgName);
    newWeb[*pNumOrg].prey = NULL;
    newWeb[*pNumOrg].numPrey = 0;

    *ppWeb = newWeb;
    *pNumOrg += 1;
}


bool addRelationToWeb(Org* pWeb, int numOrg, int predInd, int preyInd) {
    
    // TODO (Task 4): add a predator-prey relation to the food web.
    //      Inputs: 
    //          pWeb - a dynamically allocated array of Orgs, i.e. a pointer to an Org
    //          numOrg - number of organisms = size of web[], passed-by-value
    //          predInd - predator index in pWeb[]; an entry to its prey[] subitem will be added
    //          preyInd - prey index in pWeb[]; will be added to predator's prey[] subitem
    //      Outputs:
    //          web - array is updated and implicitly returned (previously allocated on heap)
    //          bool return true if the new relation was successfully added to the web; 
    //               return false if any issue occurs that prevents the new relation from being added
    //                  ex: if either the predator or prey index argument is not a valid index of pWeb[],
    //                      then print "Invalid predator and/or prey index. No relation added to the food web."
    //                      and immediately leave the function with a false return.
    //                  ex: if the relation is already a part of the web, 
    //                      then print "Duplicate predator/prey relation. No relation added to the food web."
    //                      and immediately leave the function with a false return.
    //        
    //      For the predator-prey relation...
    //      (1) if the predator's prey[] array is empty, the prey subitem will be NULL; 
    //          in this case, allocate memory for one index; 
    //      (2) otherwise, reallocate predator's prey[] array to allow one additional index; 
    //          this reallocation step must be done with only a call to malloc (i.e. not realloc());
    //          make sure to free the memory associated with the original prey[] array once the prey 
    //          indices have been copied over to the new memory allocation;
    //      (3) append the prey index as the last element of the predator's prey[] array;
    //      (4) update the numPrey subitem for the predator appropriately.

    if(predInd >= numOrg || preyInd >= numOrg || predInd < 0 || preyInd < 0){
        printf("Invalid predator and/or prey index. No relation added to the food web.\n");
        return false;
    }

    int numPreySize = pWeb[predInd].numPrey;

    // return false if duplicates are found
    for(int i = 0; i < numPreySize; i++){
        if(pWeb[predInd].prey[i] == preyInd){
            printf("Duplicate predator/prey relation. No relation added to the food web.\n");
            return false;
            
        }
    }

    int* newPrey = (int*) malloc(sizeof(int) * (numPreySize + 1));
    if(newPrey == NULL){
        return false;
    }

    // copy all the elements of the prey array into the new prey array
    // add the new element to the array
    for(int i = 0; i < numPreySize; i++){
        newPrey[i] = pWeb[predInd].prey[i];
    }

    newPrey[numPreySize] = preyInd;

    // free the old array and set the pointer to the new array
    if(pWeb[predInd].prey != NULL){
        free(pWeb[predInd].prey);
    }

    pWeb[predInd].prey = newPrey;
    
    pWeb[predInd].numPrey += 1;

    return true; // update this return statement

}

    
bool removeOrgFromWeb(Org** ppWeb, int* pNumOrg, int index) {

    // TODO (Task 7): remove the organism associated with [index] from web.
    //      Inputs: 
    //          ppWeb - a pointer to a dynamically allocated array of Orgs; i.e. a pointer to a pointer
    //          pNumOrg - a passed-by-pointer parameter for the number of organisms = size of web[]
    //          index - organism index in the (*ppWeb)[] array to remove
    //      Outputs:
    //          ppWeb - the Org array must be reallocated with less memory once the organism is removed
    //          pNumOrg - the number of organisms may decrease by one to account for the removed organism
    //          bool return true if the organism was successfully removed from the web; 
    //               return false if any issue occurs that prevents the organism from being removed
    //                  ex: if the index argument is not a valid index of (*ppWeb)[],
    //                      then print "Invalid extinction index. No organism removed from the food web."
    //                      and immediately leave the function with a false return.
    //
    //      Remember to do the following:
    //      1. remove organism at index from (*ppWeb)[] - DO NOT use realloc(), instead...
    //          (a) free any malloc'd memory associated with organism at index; i.e. its prey[] subitem
    //          (b) malloc new space for the array with the new number of Orgs
    //          (c) copy all but one of the old array elements to the new array, 
    //              some require shifting forward to overwrite the organism at index
    //          (d) free the old array
    //          (e) update the array pointer to the new array
    //          (f) update pNumOrg
    //      2. remove index from all organisms' prey[] array subitems - DO NOT use realloc(), instead...
    //          (a) search for index in all organisms' prey[] arrays; when index is found:
    //                [i] malloc new space for the array with the new number of ints
    //               [ii] copy all but one of the old array elements to the new array, 
    //                    keeping the same order some require shifting forward
    //              [iii] free the old array
    //               [iv] update the array pointer to the new array
    //                [v] update the numPrey subitem accordingly
    //          (b) update all organisms' prey[] elements that are greater than index, 
    //              which have been shifted forward in the web array
    //
    //          Edge case: check the size array being malloc'ed; 
    //                     for a web with only one organism and 
    //                     that orgranism goes extinct, 
    //                     instead of malloc'ing an empty array, 
    //                     explicitly set the pointer to NULL;
    //                     see pWeb allocation in main() as an example;
    //                     similarly, if a prey[] array becomes empty 
    //                     due to extinction, explicitly set the pointer 
    //                     to NULL, instead of malloc'ing an empty array

    // Check for invalid index
    if(index >= *pNumOrg || index < 0){
        printf("Invalid extinction index. No organism removed from the food web.\n");
        return false;
    }

    // free the prey array at the specified index
    if((*ppWeb)[index].prey != NULL){
        free((*ppWeb)[index].prey);
    }

    // free the web and set to null if only 1 organism and it goes extinct
    if(*pNumOrg == 1){
        free(*ppWeb);
        *ppWeb = NULL;
        *pNumOrg = 0;
        return true;
    }

    // allocate new web with one less organism
    Org* newWeb = (Org*) malloc(sizeof(Org) * ((*pNumOrg) - 1));
    bool containsIndex[(*pNumOrg) - 1];
    if(newWeb == NULL){
        return false;
    }

    // copy all organisms except extinct one
    // check if prey subitem of each organism has the specified index
    for(int i = 0; i < index; i++){
        newWeb[i] = (*ppWeb)[i];
        // strcpy(newWeb[i].name, (*ppWeb)[i].name);
        // newWeb[i].numPrey = (*ppWeb)[i].numPrey;
        // newWeb[i].prey = (int*) malloc(sizeof(int) * newWeb[i].numPrey);

        containsIndex[i] = false;
        for(int j = 0; j < newWeb[i].numPrey; j++){
            // newWeb[i].prey[j] = (*ppWeb)[i].prey[j];

            if((*ppWeb)[i].prey[j] == index){
                containsIndex[i] = true;
            }
        }
    }

    for(int i = index + 1; i < *pNumOrg; i++){
        newWeb[i - 1] = (*ppWeb)[i];
        // strcpy(newWeb[i - 1].name, (*ppWeb)[i].name);
        // newWeb[i - 1].numPrey = (*ppWeb)[i].numPrey;
        // newWeb[i - 1].prey = (int*) malloc(sizeof(int) * newWeb[i - 1].numPrey);

        containsIndex[i - 1] = false;
        for(int j = 0; j < newWeb[i - 1].numPrey; j++){
            // newWeb[i - 1].prey[j] = (*ppWeb)[i].prey[j];

            if((*ppWeb)[i].prey[j] == index){
                containsIndex[i - 1] = true;
            }
        }
    }
    free(*ppWeb);

    // create a new prey subitem with one less if it has the specified index
    // else go thorugh each element and add them into the prey array
    // skip sepcified index
    // if element of prey array is greater than index, subratct it by one else add it directly to prey subitem
    for(int i = 0; i < (*pNumOrg) - 1; i++){
        if(containsIndex[i]){
            int numPreySize = newWeb[i].numPrey;

            if((numPreySize == 1)){
                free(newWeb[i].prey);
                newWeb[i].prey = NULL;
                newWeb[i].numPrey = 0;
                continue;            
            }
            
            int* newPrey = (int*) malloc(sizeof(int) * (numPreySize - 1));

            int preyCounter = 0;
            for(int j = 0; j < numPreySize; j++){
                if(newWeb[i].prey[j] == index){
                    continue;
                }
                else if(newWeb[i].prey[j] > index){
                    newPrey[preyCounter] = (newWeb[i].prey[j]) - 1;
                    preyCounter++;
                }
                else {
                    newPrey[preyCounter] = newWeb[i].prey[j];
                    preyCounter++;
                }
            } 
            numPreySize--;
            
            free(newWeb[i].prey);
            newWeb[i].numPrey = numPreySize;
            newWeb[i].prey = newPrey;
        }
        else{
            for(int j = 0; j < newWeb[i].numPrey; j++){
                if(newWeb[i].prey[j] > index){
                    newWeb[i].prey[j] -= 1;
                }
            }
        }
    }

    *ppWeb = newWeb;
    *pNumOrg -= 1;

    // for(int i = 0; i < *pNumOrg; i++){
    //     printf("%s |%d| ", (*ppWeb)[i].name, (*ppWeb)[i].numPrey);
    //     for(int j = 0; j < (*ppWeb)[i].numPrey; j++){
    //         printf(" %d ", (*ppWeb)[i].prey[j]);
    //     }
    //     printf("\n");
    // }

    return true; // update this return statement
}


void freeWeb(Org* pWeb, int numOrg) {

    // TODO (Task 5): free all malloc'd memory associated with pWeb, 
    //               to prevent potential leaks before program terminates

    // free all the prey subitems if they arent set to null
    for(int i = 0; i < numOrg; i++){
        if(pWeb[i].prey != NULL){
            free(pWeb[i].prey);
        }
        
    }
    free(pWeb);
    }


void printWeb(Org* pWeb, int numOrg) {
    // TODO (Task 6): print the Food Web Organisms with what they eat (i.e. prey)

    // Example:
    //   (0) Grass
    //   (1) Lion eats Zebra
    //   (2) Zebra eats Grass

    // print each organism and what it eats formatted properly
    for(int i = 0; i < numOrg; i++){
        printf("  (%d) %s", i, pWeb[i].name);
        if(pWeb[i].numPrey > 0){
            int preyIndex = pWeb[i].prey[0];
            printf(" eats %s", pWeb[preyIndex].name);
            for(int j = 1; j < pWeb[i].numPrey; j++){
                preyIndex = pWeb[i].prey[j];
                printf(", %s", pWeb[preyIndex].name);
            }
        }
        printf("\n");
    }

}


void printApexPred(Org* pWeb, int numOrg) {
    int apexArr[numOrg];

    for(int i = 0; i < numOrg; i++){
        apexArr[i] = 0;
    }

    // check if organism is being eaten by others
    // if current organism is in the prey array of another organism then increment the apexArr at its element
    for(int i = 0; i < numOrg; i++){
        int preySize = pWeb[i].numPrey;
        for(int j = 0; j < preySize; j++){
            int preyIndex = pWeb[i].prey[j];
            apexArr[preyIndex] += 1;
        }
    }

    // print all elements of apexArr when its 0
    for(int i = 0; i < numOrg; i++){
        if(apexArr[i] == 0){
            printf("  %s\n", pWeb[i].name);
        }
    }
}


void printFlexibleEaters(Org* pWeb, int numOrg) {
    int max = 0;

    // max is the organism with the highest num prey
    for(int i = 0; i < numOrg; i++){
        if(pWeb[i].numPrey > max){
            max = pWeb[i].numPrey;
        }
    }

    for(int i = 0; i < numOrg; i++){
        if(pWeb[i].numPrey == max){
            printf("  %s\n", pWeb[i].name);
        }
    }
}


void printProducer(Org* pWeb, int numOrg) {
    // producers are organisms with num prey = 0
    for(int i = 0; i < numOrg; i++){
        if(pWeb[i].numPrey == 0){
            printf("  %s\n", pWeb[i].name);
        }
    }
}


void printTastiest(Org* pWeb, int numOrg) {
    int tastyArr[numOrg];

    for(int i = 0; i < numOrg; i++){
        tastyArr[i] = 0;
    }

    // find how many times each organism is being eaten
    // increment organism in tasty array
    for(int i = 0; i < numOrg; i++){
        int preySize = pWeb[i].numPrey;
        for(int j = 0; j < preySize; j++){
            int preyIndex = pWeb[i].prey[j];
            tastyArr[preyIndex] += 1;
        }
    }

    // find the organism eating the most
    int max = tastyArr[0];
    for(int i = 0; i < numOrg; i++){
        if(tastyArr[i] > max){
            max = tastyArr[i];
        }
    }

    // print all organims with the max eaten size
    for(int i = 0; i< numOrg; i++){
        if(tastyArr[i] == max){
            printf("  %s\n", pWeb[i].name);
        }
    }
}


void printHeights(Org* pWeb, int numOrg) {
    int heights[numOrg];

    for(int i = 0; i < numOrg; i++){
        heights[i] = 0;
    }

    // go through each organsim and find the max height in its prey array
    // set its own height to +1 of max
    // keep looping until no heights are changed
    bool changed = true;
    while(changed){
        changed = false;
        for(int i = 0; i < numOrg; i++){
            int max = 0;

            for(int j = 0; j < pWeb[i].numPrey; j++){
                int preyIndex = pWeb[i].prey[j];

                if(heights[preyIndex] > max){
                    max = heights[preyIndex];
                }
            }

            max++;
            if(pWeb[i].numPrey > 0 && max > heights[i]){
                heights[i] = max;
                changed = true;
            }
        }
    }

    for(int i = 0; i < numOrg; i++){
        printf("  %s: %d\n", pWeb[i].name, heights[i]);
    }
}

void printVore(Org* pWeb, int numOrg) {
    int producers[numOrg];
    int herbivores[numOrg];
    int omnivores[numOrg];
    int carnivores[numOrg];

    for(int i = 0; i < numOrg; i++){
        producers[i] = 0;
        herbivores[i] = 0;
        omnivores[i] = 0;
        carnivores[i] = 0;
    }

    // all organisms with num prey = 0 is a producer
    for(int i = 0; i < numOrg; i++){
        if(pWeb[i].numPrey == 0){
            producers[i] = 1;
        }
    }

    // check if organsim only easts producers
    for(int i = 0; i < numOrg; i++){
        if(producers[i] == 0){
            herbivores[i] = 1;
            for(int j = 0; j < pWeb[i].numPrey; j++){
                int preyIndex = pWeb[i].prey[j];
                if(pWeb[preyIndex].numPrey > 0){
                    herbivores[i] = 0;
                }
            }
        }
    }

    // if organsim eats any producers then remove it from carnovore array
    for(int i = 0; i < numOrg; i++){
        if(producers[i] == 0 && herbivores[i] == 0){
            carnivores[i] = 1;
            for(int j = 0; j < pWeb[i].numPrey; j++){
                int preyIndex = pWeb[i].prey[j];
                if(pWeb[preyIndex].numPrey == 0){
                    carnivores[i] = 0;
                }
            }
        }
    }

    // all other organsims are omnivores
    for(int i = 0; i < numOrg; i++){
        if(producers[i] == 0 && herbivores[i] == 0 && carnivores[i] == 0){
            omnivores[i] = 1;
        }
    }

    printf("  Producers:\n");
    for(int i = 0; i < numOrg; i++){
        if(producers[i] == 1){
            printf("    %s\n", pWeb[i].name);
        }
    }

    printf("  Herbivores:\n");
    for(int i = 0; i < numOrg; i++){
        if(herbivores[i] == 1){
            printf("    %s\n", pWeb[i].name);
        }
    }

    printf("  Omnivores:\n");
    for(int i = 0; i < numOrg; i++){
        if(omnivores[i] == 1){
            printf("    %s\n", pWeb[i].name);
        }
    }

    printf("  Carnivores:\n");
    for(int i = 0; i < numOrg; i++){
        if(carnivores[i] == 1){
            printf("    %s\n", pWeb[i].name);
        }
    }

}

void displayAll(Org* pWeb, int numOrg, bool modified) {

    if (modified) printf("UPDATED ");
    printf("Food Web Predators & Prey:\n");
    printWeb(pWeb,numOrg); 
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Apex Predators:\n");
    // TODO (Task 6): identify and print the organisms not eaten by any others
    printApexPred(pWeb,numOrg);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Producers:\n");
    // TODO (Task 6): identify and print the organisms that eat no other organisms
    printProducer(pWeb,numOrg);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Most Flexible Eaters:\n");
    // TODO (Task 6): identity and print the organism(s) with the most prey
    printFlexibleEaters(pWeb, numOrg);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Tastiest Food:\n");
    // TODO (Task 6): identity and print organism(s) eaten by the most other organisms
    printTastiest(pWeb, numOrg);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Food Web Heights:\n");
    // TODO (Task 6): calculate and print the length of the longest chain from any 
    //                producer to each organism
    printHeights(pWeb, numOrg);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Vore Types:\n");
    // TODO (Task 6): classify all organisms and print each group
    //                (producers, herbivores, omnivores, & carnivores)
    printVore(pWeb, numOrg);
    printf("\n");

}

bool setModes(int argc, char* argv[], bool* pBasicMode, bool* pDebugMode, bool* pQuietMode) {

    // TODO (Task 2): process command-line arguments & update basicMode, debugMode, and quietMode
    //                using the passed-by-pointer parameters pBasicMode, pDebugMode, and pQuietMode
    //
    //      - default values: basicMode = FALSE, debugMode = FALSE, quietMode = FALSE
    //      - if basicMode = TRUE, then only build the initial web and analyze it; no modifications
    //      - if debugMode = TRUE, then print out full web as it is built & modified at each step
    //      - if quietMode = TRUE, then suppress printed user-input prompt messages        
    //      
    //      valid command-line arguments are "-b", "-d", and "-q" (and can only appear once);
    //      ALSO, allow full-word command-line arguments "-basic", "-debug", and "-quiet" by simply 
    //      checking if the first two characters are "-b", "-d", and "-q", respectively.
    //      - set basicMode = TRUE if "-b" or "-basic" (or "-bas" or "-basicmode" etc. ) is present
    //      - set debugMode = TRUE if "-d" or "-debug" (or "-deb" or "-debugmode" etc. ) is present
    //      - set quietMode = TRUE if "-q" or "-quiet" (or "-qui" or "-quietmode" etc. ) is present
    //      - if an invalid OR duplicate command-line argument is present, return false from the 
    //        function, which results in the program terminating immediately after the following 
    //        print statment in main():
    //              "Invalid command-line argument. Terminating program..."
    //        otherwise, return true after updating the relevant passed-by-pointer mode parameters
    //
    //      once command-line arguments are processed, the program settings are printed in main()
    //      - Ex: if the program is run as "./a.out -q -b", then print
    //              Program Settings:
    //                basic mode = ON
    //                debug mode = OFF
    //                quiet mode = ON
    //      - Ex: if the program is run as "./a.out", then print
    //              Program Settings:
    //                basic mode = OFF
    //                debug mode = OFF
    //                quiet mode = OFF
    //
    for(int i = 1; i < argc; i++){

        // check if first 2 chars of the string is a -b or -d or -q
        // else return false

        if(argv[i][0] == '-' && argv[i][1] == 'b' && *pBasicMode == false){
            *pBasicMode = true;
            
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'd' && *pDebugMode == false){
            *pDebugMode = true;
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'q' && *pQuietMode == false){
            *pQuietMode = true;
        }
        else{
            
            return false;
        }
        // printf("%b %b %b\n", *pBasicMode, *pDebugMode, *pQuietMode);
        
    }
    
    return true; // update this return statement

}


void printONorOFF(bool mode) {
    if (mode) {
        printf("ON\n");
    } else {
        printf("OFF\n");
    }
}


int main(int argc, char* argv[]) {  

    // -----------------------------------------------------------------------------------------------------
    // TODO (Task 1): add comments to the main application to show understanding
    //  DO NOT MODIFY THE CODE BENEATH THIS COMMENT (except for debugging purposes and adding comments).
    //  The code in main() represents the primary application, which has been provided for you.
    //  There are many calls to functions that you must write above. Read through the code below, understand  
    //  how it works, check how functions are called, and add relevant comments to show your understanding.
    //  However, no changes should be made to the code in main(). You can put in debugging print statements, 
    //  but those should be removed or commented out prior to submitting to the autograder.
    // -----------------------------------------------------------------------------------------------------
    
    // Initialize modes
    bool basicMode = false;
    bool debugMode = false;
    bool quietMode = false;

    // Check the command line arguments for checking if each mode has been set
    if (!setModes(argc, argv, &basicMode, &debugMode, &quietMode)) {
        printf("Invalid command-line argument. Terminating program...\n");
        return 1;
    }

    // Print out the setting for each mode
    printf("Program Settings:\n");
    printf("  basic mode = ");
    printONorOFF(basicMode);
    printf("  debug mode = ");
    printONorOFF(debugMode);
    printf("  quiet mode = ");
    printONorOFF(quietMode);
    printf("\n");
    
    // Initial number of organisms set to 0 and pointer to the food web is set to NULL
    int numOrgs = 0;
    printf("Welcome to the Food Web Application\n\n");
    printf("--------------------------------\n\n");

    Org* pWeb = NULL;

    printf("Building the initial food web...\n");
    
    // Add the first organism to the food web
    if (!quietMode) printf("Enter the name for an organism in the web (or enter DONE): ");
    char tempName[20] = "";
    scanf("%s",tempName); 
    if (!quietMode) printf("\n");

    // Keep adding organisms to the food web until user enters done
    while (strcmp(tempName,"DONE") != 0) {
        addOrgToWeb(&pWeb,&numOrgs,tempName);
        
        // Prints the web after every modification
        if (debugMode) {
            printf("DEBUG MODE - added an organism:\n");
            printWeb(pWeb,numOrgs);
            printf("\n");
        }

        if (!quietMode) printf("Enter the name for an organism in the web (or enter DONE): ");
        scanf("%s",tempName); 
        if (!quietMode) printf("\n");
    }
    if (!quietMode) printf("\n");

    // Enter the predator/prey relationships between the organisms in the food web
    if (!quietMode) printf("Enter the pair of indices for a predator/prey relation.\n");
    if (!quietMode) printf("Enter any invalid index when done (-1 2, 0 -9, 3 3, etc.).\n");
    if (!quietMode) printf("The format is <predator index> <prey index>: ");
        
    // Enter predator/prey indices
    int predInd, preyInd;
    scanf("%d %d",&predInd, &preyInd);
    if (!quietMode) printf("\n");

    // Keep looping until input is invalid
    while (predInd >= 0 && preyInd >= 0 && predInd < numOrgs &&  preyInd < numOrgs && predInd != preyInd) {
        addRelationToWeb(pWeb,numOrgs,predInd,preyInd);
        
        // Print updated food web
        if (debugMode) {
            printf("DEBUG MODE - added a relation:\n");
            printWeb(pWeb,numOrgs);
            printf("\n");
        }

        if (!quietMode) printf("Enter the pair of indices for a predator/prey relation.\n");
        if (!quietMode) printf("Enter any invalid index when done (-1 2, 0 -9, 3 3, etc.).\n");
        if (!quietMode) printf("The format is <predator index> <prey index>: ");
        
        scanf("%d %d",&predInd, &preyInd);  
        if (!quietMode) printf("\n");
    }
    printf("\n");

    // Display initial food web
    printf("--------------------------------\n\n");
    printf("Initial food web complete.\n");
    printf("Displaying characteristics for the initial food web...\n");
    
    displayAll(pWeb,numOrgs,false);

    // Allow to modify the food web if not in basic mode
    if (!basicMode) {
        printf("--------------------------------\n\n");
        printf("Modifying the food web...\n\n");
        char opt = '?';

        // Menu for modifying the food web
        while (opt != 'q') {
            if (!quietMode) {
                printf("Web modification options:\n");
                printf("   o = add a new organism (expansion)\n");
                printf("   r = add a new predator/prey relation (supplementation)\n");
                printf("   x = remove an organism (extinction)\n");
                printf("   p = print the updated food web\n");
                printf("   d = display ALL characteristics for the updated food web\n");
                printf("   q = quit\n");
                printf("Enter a character (o, r, x, p, d, or q): ");
            }
            scanf(" %c", &opt);
            if (!quietMode) printf("\n\n");

            // Add new organism to the food web
            if (opt == 'o') {
                char newName[20];
                if (!quietMode) printf("EXPANSION - enter the name for the new organism: ");
                scanf("%s",newName);
                if (!quietMode) printf("\n");
                printf("Species Expansion: %s\n", newName);
                addOrgToWeb(&pWeb,&numOrgs,newName);
                printf("\n");

                if (debugMode) {
                    printf("DEBUG MODE - added an organism:\n");
                    printWeb(pWeb,numOrgs);
                    printf("\n");
                }

            } 
            // Take out organism from the food web
            else if (opt == 'x') {
                int extInd;
                if (!quietMode) printf("EXTINCTION - enter the index for the extinct organism: ");
                scanf("%d",&extInd);
                if (!quietMode) printf("\n");
                if (extInd >= 0 && extInd < numOrgs) {
                    printf("Species Extinction: %s\n", pWeb[extInd].name);
                    removeOrgFromWeb(&pWeb,&numOrgs,extInd);
                } else {
                    printf("Invalid index for species extinction\n");
                }
                printf("\n");
                
                if (debugMode) {
                    printf("DEBUG MODE - removed an organism:\n");
                    printWeb(pWeb,numOrgs);
                    printf("\n");
                }

            } 
            // Add new predator/prey relationship
            else if (opt == 'r') {
                if (!quietMode) printf("SUPPLEMENTATION - enter the pair of indices for the new predator/prey relation.\n");
                if (!quietMode) printf("The format is <predator index> <prey index>: ");
                scanf("%d %d",&predInd, &preyInd);
                if (!quietMode) printf("\n");

                if (addRelationToWeb(pWeb,numOrgs,predInd,preyInd)) {
                    printf("New Food Source: %s eats %s\n", pWeb[predInd].name, pWeb[preyInd].name);
                };
                printf("\n");
                if (debugMode) {
                    printf("DEBUG MODE - added a relation:\n");
                    printWeb(pWeb,numOrgs);
                    printf("\n");
                }

            } 
            // Print the food web
            else if (opt == 'p') {
                printf("UPDATED Food Web Predators & Prey:\n");
                printWeb(pWeb,numOrgs);
                printf("\n");
                
            } else if (opt == 'd') {
                printf("Displaying characteristics for the UPDATED food web...\n\n");
                displayAll(pWeb,numOrgs,true);

            }
            printf("--------------------------------\n\n");
        
        }
        
    }

    // Free the memory
    freeWeb(pWeb,numOrgs);

    //printf("\n\n");

    return 0;
}

