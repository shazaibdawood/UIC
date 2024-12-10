// Shazaib Dawood
// CS 211
// Popular Vote Minimizer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

int totalEVs(State* states, int szStates) {
    //----------------------------------------------   
    // TODO: Task 1 - write the totalEVs() function;
    //                note test_totalEVs() is 
    //                provided in test.c to test
    //                the functionality of totalEVs();
    //                update makefile to build and run
    //                testing suite as follows:
    //                   -> make build_test
    //                   -> make run_test 
    //----------------------------------------------
    int total = 0;

    for(int i = 0; i < szStates; i++){
        total += states[i].electoralVotes;
    }
    return total; // modify or replace this line
}

int totalPVs(State* states, int szStates) {
    //--------------------------------------------------   
    // TODO: Task 1 - write the totalPVs() function;
    //                then, write your own test function 
    //                test_totalPVs() in test.c;
    //                update makefile to build and run
    //                testing suite as follows:
    //                   -> make build_test
    //                   -> make run_test 
    //--------------------------------------------------
    int total = 0;

    for(int i = 0; i < szStates; i++){
        total += states[i].popularVotes;
    }
    return total; // modify or replace this line
}

bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    //------------------------------------------------   
    // TODO: Task 2 - write the setSettings() function
    //------------------------------------------------
    *year = 0; 
    *quietMode = false; 
    *fastMode = false; 
    bool isValid = true;
    
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-f") == 0){ //Set fast mode
            *fastMode = true;
        }
        else if(strcmp(argv[i], "-q") == 0){ //set quiet mode
            *quietMode = true;
        }
        else if(strcmp(argv[i], "-y") == 0){ //set year
            if(i < argc - 1){ //check if year is out of bounds
                i++; //skip next argument
                if(sscanf(argv[i], "%d", year) != 1){ //check for integer after -y
                    *year = 0;
                }
                // *year = atoi(argv[i]);
                if(*year % 4 != 0 || *year < 1828 || *year > 2020){ //check year is invalid
                    *year = 0;
                }
            }
            else{
                isValid = false; //no element for year after -y
            }
            
        }
        else{
            isValid = false;
        }

    }
    
    return isValid; //modify or replace this
}

void inFilename(char* filename, int year) {
    //------------------------------------------------   
    // TODO: Task 3 - write the inFilename() function
    //------------------------------------------------
    snprintf(filename, 14, "data/%d.csv", year);
}

void outFilename(char* filename, int year) {
    //------------------------------------------------   
    // TODO: Task 3 - write the outFilename() function
    //------------------------------------------------
    snprintf(filename, 19, "toWin/%d_win.csv", year);
}

bool parseLine(char* line, State* myState) {
    //------------------------------------------------   
    // TODO: Task 5 - write the parseLine() function
    //------------------------------------------------
    int commas = 0;
    for(int i = 0; i < strlen(line); i++){ //count the commas
        if(line[i] == ','){
            commas++;
        }
    }
    if(line[strlen(line) - 1] == '\n'){ //remove the newline if it exists
        line[strlen(line) - 1] = '\0';
    }

    if(commas != 3){
        return false;
    }

    char* wordstart = line;
    char* wordend = strchr(wordstart, ',');
    int wordlen = wordend - wordstart;

    strncpy(myState->name, wordstart, wordlen); //get the name
    myState->name[wordlen] = '\0';

    wordstart = wordend + 1;
    wordend = strchr(wordstart, ',');
    wordlen = wordend - wordstart;

    strncpy(myState->postalCode, wordstart, 2); //get the postal code
    myState->postalCode[2] = '\0';

    wordstart = wordend + 1;
    wordend = strchr(wordstart, ',');
    myState->electoralVotes = atoi(wordstart); // get electoral votes

    wordstart = wordend + 1;
    myState->popularVotes = atoi(wordstart); //get popular votes
    

    return true; //modify or replace this
}

bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0; //required initialization prior to incrementing. 
    //-----------------------------------------------------   
    // TODO: Task 6 - write the readElectionData() function
    //-----------------------------------------------------
    FILE* datafile = fopen(filename, "r");
    if(datafile == NULL){
        return false;
    }

    char line[100];
    while(fgets(line, sizeof(line), datafile) != NULL){ //parse each line
        if(parseLine(line, &allStates[*nStates])){
            (*nStates)++;
        }
    }
    fclose(datafile);
    return true; //modify or replace this
}

MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    //----------------------------------------------   
    // TODO: Task 7 - write minPopVoteAtLeast();
    //                a recursive helper function;
    //                returns MinInfo for the subset
    //                of [states] from index [start]
    //                to the end with the minimum
    //                popular vote total that has 
    //                sufficient [EVs] to win
    //---------------------------------------------- 
    MinInfo result; // modify or replace this line
    result.szSomeStates = 0; // modify or replace this line
    result.subsetPVs = 0; //empty subset
    result.sufficientEVs = false;

    //base case 1
    //ev is sufficient
    if(start == szStates){
        result.sufficientEVs = (EVs <= 0);
        return result;
    }

    //base case 2
    //EV requiremnt already reached
    if(EVs <= 0){
        result.sufficientEVs = true;
        return result;
    }
    
    //recursive case 1
    //include state
    MinInfo includeState = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);
    includeState.subsetPVs += (states[start].popularVotes / 2) + 1; //add PVs
    includeState.someStates[includeState.szSomeStates++] = states[start]; //add to subset

    //recursive case 2
    //exclude state
    MinInfo excludeState = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    if (includeState.sufficientEVs && excludeState.sufficientEVs) {
    if (includeState.subsetPVs < excludeState.subsetPVs) {
        return includeState;
    } else {
        return excludeState;
    }
    } else if (includeState.sufficientEVs) {
        return includeState;
    } else {
        return excludeState;
    }
}

MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    //----------------------------------------------   
    // TODO: Task 8 - write minPopVoteAtLeastFast();
    //                start by copying in fully
    //                functioning code from 
    //                minPopVoteAtLeast() and make
    //                additions for memoization
    //---------------------------------------------- 
    MinInfo result; // modify or replace this line
    result.szSomeStates = 0; // modify or replace this line
    result.subsetPVs = 0; //empty subset
    result.sufficientEVs = false;

    //base case 1
    //ev is sufficient
    if(start == szStates){
        result.sufficientEVs = (EVs <= 0);
        return result;
    }

    //base case 2
    //EV requiremnt already reached
    if(EVs <= 0){
        result.sufficientEVs = true;
        return result;
    }

    //base case 3
    // Result already found
    if(memo[start][EVs].subsetPVs!=-1){
        return memo[start][EVs];
    }

    //recursive case 1
    //include state
    MinInfo includeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);
    includeState.subsetPVs += (states[start].popularVotes / 2) + 1;
    includeState.someStates[includeState.szSomeStates] = states[start];
    includeState.szSomeStates++;

    //recursive case 2
    //exclude state
    MinInfo excludeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);

    if (includeState.sufficientEVs && excludeState.sufficientEVs) {
        if (includeState.subsetPVs < excludeState.subsetPVs) {
            result = includeState;
        } else {
            result = excludeState;
        }
    } else if (includeState.sufficientEVs) {
        result = includeState;
    } else {
        result = excludeState;
    }

    //memoization
    memo[start][EVs] = result;
    return result;
}

MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo result = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    
    //----------------------------------------------   
    // TODO: Task 8 - [memo] will go out of scope 
    //                upon return, so free all
    //                heap-allocated memory for 
    //                [memo] before return 
    //---------------------------------------------- 

    for(int i = 0; i <= szStates; i++){
        free(memo[i]);
    }
    free(memo);

    return result;
}

bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    //-----------------------------------------------------   
    // TODO: Task 9 - write the writeSubsetData() function
    //-----------------------------------------------------
    FILE* file = fopen(filenameW, "w");
    if(file == NULL){
        return false;
    }

    int wonPVs = toWin.subsetPVs;
    fprintf(file, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs,wonPVs);

    for(int i = toWin.szSomeStates - 1; i >= 0; i--){
        State myState = toWin.someStates[i];
        int popWinVotes = (myState.popularVotes / 2) + 1;
        fprintf(file, "%s,%s,%d,%d\n", myState.name,myState.postalCode,myState.electoralVotes, popWinVotes);
    }

    fclose(file);
    return true; //modify or replace this
}
