#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool test_totalEVs() {
    State aStates[10];
    int res;
    
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 12, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return false;
    }
    printf(" Checking totalEVs() for 6 States:\n");
    res = totalEVs(aStates,6);
    if (res != 48) {
        printf("  individual state EVs are 5, 8, 12, 6, 7, 10\n");
        printf("  expected total EVs = 48, actual total EVs = %d\n",res);
        return false;
    }

    //--------------------------------------------------------   
    // TODO: Task 1 - perform additional testing to make this 
    //                test case for totalEVs() more robust
    //--------------------------------------------------------   
    
    printf(" Checking totalEVs() for 0 States:\n");
    res = totalEVs(aStates,0);
    if (res != 0) {
        printf("  expected total EVs = 0, actual total EVs = %d\n",res);
        return false;
    }

    printf(" Checking totalEVs() for 1 State:\n");
    res = totalEVs(aStates,1);
    if (res != 5) {
        printf("  expected total EVs = 5, actual total EVs = %d\n",res);
        return false;
    }

    aStates[0].electoralVotes = -10;
    aStates[1].electoralVotes = 3;
    aStates[2].electoralVotes = -2;

    printf(" Checking totalEVs() for negative votes:\n");
    res = totalEVs(aStates,3);
    if (res != -9) {
        printf("  individual state EVs are -10, 3, -2\n");
        printf("  expected total EVs = 9, actual total EVs = %d\n",res);
        return false;
    }

    return true;
}

bool test_totalPVs() {
    //--------------------------------------------------------   
    // TODO: Task 1 - write your own test case for totalPVs();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //--------------------------------------------------------
    State aStates[10];
    int res;
    
    aStates[0].popularVotes = 5;
    aStates[1].popularVotes = 8;
    aStates[2].popularVotes = 12;
    aStates[3].popularVotes = 6;
    aStates[4].popularVotes = 7;
    aStates[5].popularVotes = 10;

    printf(" Checking totalPVs() for 0 States:\n");
    res = totalPVs(aStates,0);
    if (res != 0) {
        printf("  expected total PVs = 0, actual total PVs = %d\n",res);
        return false;
    }

    printf(" Checking totalPVs() for 1 State:\n");
    res = totalPVs(aStates,1);
    if (res != 5) {
        printf("  expected total PVs = 5, actual total PVs = %d\n",res);
        return false;
    }

    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5);
    if (res != 38) {
        printf("  individual state PVs are 5, 8, 12, 6, 7\n");
        printf("  expected total PVs = 38, actual total PVs = %d\n",res);
        return false;
    }
    printf(" Checking totalPVs() for 6 States:\n");
    res = totalPVs(aStates,6);
    if (res != 48) {
        printf("  individual state PVs are 5, 8, 12, 6, 7, 10\n");
        printf("  expected total PVs = 48, actual total PVs = %d\n",res);
        return false;
    }

    aStates[0].popularVotes = -10;
    aStates[1].popularVotes = 3;
    aStates[2].popularVotes = -2;

    printf(" Checking totalPVs() for negative votes:\n");
    res = totalPVs(aStates,3);
    if (res != -9) {
        printf("  individual state PVs are -10, 3, -2\n");
        printf("  expected total PVs = 9, actual total PVs = %d\n",res);
        return false;
    }

    return true;
}

bool test_setSettings() {
    //-----------------------------------------------------------   
    // TODO: Task 2 - write your own test case for setSettings();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    char* argv[] = {"./app.exe", "-f", "-q", "-y", "2020"};
    int argc = 5;
    int year = 0;
    bool fastMode = false;
    bool quietMode = false;
    
    printf(" Checking setSettings() for valid arguments:\n");
    if(!setSettings(argc, argv, &year, &fastMode, &quietMode) || year != 2020 || fastMode != true || quietMode != true){
        printf("  argv = {./app.exe,-f,-q,-y,2020}\n");
        printf("  expected values: year = 2020, fastmode = 1, quietmode = 1\n");
        printf("  actual values:   year = %d, fastmode = %b, quietmode = %b\n", year, fastMode, quietMode);
        
        return false;
    }

    argv[2] = "-g";
    printf(" Checking setSettings() for invalid arguments:\n");
    if(setSettings(argc, argv, &year, &fastMode, &quietMode)){
        printf("  argv = {./app.exe,-f,-g,-y,2020}\n");
        printf("  expected values: year = 2020, fastmode = 1, quietmode = 0\n");
        printf("  actual values:   year = %d, fastmode = %b, quietmode = %b\n", year, fastMode, quietMode);
        
        return false;
    }

    char* argv2[] = {"./app.exe", "-f", "-q", "-y"};
    argc = 4;
    printf(" Checking setSettings() for no argument after -y:\n");
    if(setSettings(argc, argv2, &year, &fastMode, &quietMode)){
        printf("  argv = {./app.exe, -f, -q, -y}\n");
        printf("  expected values: year = 0, fastmode = 1, quietmode = 1\n");
        printf("  actual values:   year = %d, fastmode = %b, quietmode = %b\n", year, fastMode, quietMode);
        
        return false;
    }

    char* argv3[] = {"./app.exe", "-y", "-q", "-f"};
    printf(" Checking setSettings() for non-integer argument after -y:\n");
    if(!setSettings(argc, argv3, &year, &fastMode, &quietMode) || year != 0 || fastMode != true || quietMode != false){
        printf("  argv = {./app.exe, -y, -q, -f}\n");
        printf("  expected values: year = 0, fastmode = 1, quietmode = 1\n");
        printf("  actual values:   year = %d, fastmode = %b, quietmode = %b\n", year, fastMode, quietMode);
        
        return false;
    }

    char* argv4[] = {"./app.exe", "-y", "20", "-q", "-f"};
    argc = 5;
    printf(" Checking setSettings() for invalid year:\n");
    if(!setSettings(argc, argv4, &year, &fastMode, &quietMode) || year != 0 || fastMode != true || quietMode != true){
        printf("  argv = {./app.exe, -y, -q, -f}\n");
        printf("  expected values: year = 0, fastmode = 1, quietmode = 1\n");
        printf("  actual values:   year = %d, fastmode = %b, quietmode = %b\n", year, fastMode, quietMode);
        
        return false;
    }

    char* argv5[] = {"./app.exe"};
    argc = 1;
    printf(" Checking setSettings() for empty argv:\n");
    if(!setSettings(argc, argv5, &year, &fastMode, &quietMode) || year != 0 || fastMode != false || quietMode != false) {
        printf("  argv = {./app.exe}\n");
        printf("  expected values: year = 0, fastmode = 0, quietmode = 0\n");
        printf("  actual values:   year = %d, fastmode = %d, quietmode = %d\n", year, fastMode, quietMode);
        return false;
    }

    char* argv6[] = {"./app.exe", "-f"};
    argc = 2;
    printf(" Checking setSettings() for -f only:\n");
    if(!setSettings(argc, argv6, &year, &fastMode, &quietMode) || year != 0 || fastMode != true || quietMode != false) {
        printf("  argv = {./app.exe, -f}\n");
        printf("  expected values: year = 0, fastmode = 1, quietmode = 0\n");
        printf("  actual values:   year = %d, fastmode = %d, quietmode = %d\n", year, fastMode, quietMode);
        return false;
    }

    char* argv7[] = {"./app.exe", "-q"};
    argc = 2;
    printf(" Checking setSettings() for -q only:\n");
    if(!setSettings(argc, argv7, &year, &fastMode, &quietMode) || year != 0 || fastMode != false || quietMode != true) {
        printf("  argv = {./app.exe, -q}\n");
        printf("  expected values: year = 0, fastmode = 0, quietmode = 1\n");
        printf("  actual values:   year = %d, fastmode = %d, quietmode = %d\n", year, fastMode, quietMode);
        return false;
    }

    char* argv8[] = {"./app.exe", "-y"};
    argc = 2;
    printf(" Checking setSettings() for -y only:\n");
    if(setSettings(argc, argv8, &year, &fastMode, &quietMode)) {
        printf("  argv = {./app.exe, -y}\n");
        printf("  expected values: year = 0, fastmode = 0, quietmode = 0\n");
        printf("  actual values:   year = %d, fastmode = %d, quietmode = %d\n", year, fastMode, quietMode);
        return false;
    }

    char* argv9[] = {"./app.exe", "-y", "20"};
    argc = 3;
    printf(" Checking setSettings() for -y and invalid year:\n");
    if(!setSettings(argc, argv9, &year, &fastMode, &quietMode) || year != 0 || fastMode != false || quietMode != false) {
        printf("  argv = {./app.exe, -y, 20}\n");
        printf("  expected values: year = 0, fastmode = 0, quietmode = 0\n");
        printf("  actual values:   year = %d, fastmode = %d, quietmode = %d\n", year, fastMode, quietMode);
        return false;
    }

    char* argv10[] = {"./app.exe", "-y", "2020"};
    argc = 3;
    printf(" Checking setSettings() for -y and valid year:\n");
    if(!setSettings(argc, argv10, &year, &fastMode, &quietMode) || year != 2020 || fastMode != false || quietMode != false) {
        printf("  argv = {./app.exe, -y, 2020}\n");
        printf("  expected values: year = 2020, fastmode = 0, quietmode = 0\n");
        printf("  actual values:   year = %d, fastmode = %d, quietmode = %d\n", year, fastMode, quietMode);
        return false;
    }

    return true; //modify this
}

bool test_inFilename() {
    //----------------------------------------------------------   
    // TODO: Task 3 - write your own test case for inFilename();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //----------------------------------------------------------

    char filename[14];

    printf("Checking inFilename() for valid year:\n");
    inFilename(filename, 2020);
    if (strcmp(filename, "data/2020.csv") != 0) {
        printf("  Expected: data/2020.csv\n");
        printf("  Actual:   %s\n", filename);
        return false;
    }

    char* argv[] = {"./app.exe", "-f", "-q", "-y", "2019"};
    int argc = 5;
    int year = 0;
    bool fastMode = false;
    bool quietMode = false;
    setSettings(argc, argv, &year, &fastMode, &quietMode);

    printf("Checking inFilename() for invalid year:\n");
    inFilename(filename, year);
    if (strcmp(filename, "data/0.csv") != 0) {
        printf("  Expected: data/0.csv\n");
        printf("  Actual:   %s\n", filename);
        return false;
    }

    return true; //modify this
}

bool test_outFilename() {
    //-----------------------------------------------------------   
    // TODO: Task 3 - write your own test case for outFilename();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    
    char filename[19];

    printf("Checking outFilename() for valid year:\n");
    outFilename(filename, 2020);
    if (strcmp(filename, "toWin/2020_win.csv") != 0) {
        printf("  Expected: toWin/2020_win.csv\n");
        printf("  Actual:   %s\n", filename);
        return false;
    }

    char* argv[] = {"./app.exe", "-f", "-q", "-y", "2019"};
    int argc = 5;
    int year = 0;
    bool fastMode = false;
    bool quietMode = false;
    setSettings(argc, argv, &year, &fastMode, &quietMode);

    printf("Checking outFilename() for invalid year:\n");
    outFilename(filename, year);
    if (strcmp(filename, "toWin/0_win.csv") != 0) {
        printf("  Expected: toWin/0_win.csv\n");
        printf("  Actual:   %s\n", filename);
        return false;
    }

    return true; //modify this
}

bool test_parseLine() {
    //---------------------------------------------------------   
    // TODO: Task 5 - write your own test case for parseLine();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //---------------------------------------------------------

    State myState;

    char line1[] = "Illinois,IL, 20, 6033744\n";
    printf("Checking parseLine() for valid input with newline:\n");
    if (!parseLine(line1, &myState) || strcmp(myState.name, "Illinois") != 0 || strcmp(myState.postalCode, "IL") != 0 || myState.electoralVotes != 20 || myState.popularVotes != 6033744) {
        printf("  Expected: name = Illinois, postalCode = IL, electoralVotes = 20, popularVotes = 6033744\n");
        printf("  Actual:   name = %s, postalCode = %s, electoralVotes = %d, popularVotes = %d\n", myState.name, myState.postalCode, myState.electoralVotes, myState.popularVotes);
        return false;
    }

    char line2[] = "Illinois,IL, 20, 6033744";
    printf("Checking parseLine() for valid input without newline:\n");
    if (!parseLine(line2, &myState) || strcmp(myState.name, "Illinois") != 0 || strcmp(myState.postalCode, "IL") != 0 || myState.electoralVotes != 20 || myState.popularVotes != 6033744) {
        printf("  Expected: name = Illinois, postalCode = IL, electoralVotes = 20, popularVotes = 6033744\n");
        printf("  Actual:   name = %s, postalCode = %s, electoralVotes = %d, popularVotes = %d\n", myState.name, myState.postalCode, myState.electoralVotes, myState.popularVotes);
        return false;
    }

    char line3[] = "Illinois,IL, 20";
    printf("Checking parseLine() for missing comma:\n");
    if (parseLine(line3, &myState)) {
        printf("  Expected: false return\n");
        return false;
    }

    return true; //modify this
}

bool test_readElectionData() {
    //----------------------------------------------------------------   
    // TODO: Task 6 - write your own test case for readElectionData();
    //                make sure to test all components
    //----------------------------------------------------------------
    State allStates[51];
    int nStates;
    bool result;

    printf("Checking readElectionData() for a valid file:\n");
    result = readElectionData("data/1828.csv", allStates, &nStates);
    if (!result || nStates != 24 || strcmp(allStates[0].name, "Alabama") != 0 || strcmp(allStates[0].postalCode, "AL") != 0 || allStates[0].electoralVotes != 5 || allStates[0].popularVotes != 18618) {
        printf("  Expected: true\n");
        return false;
    } //Alabama,AL,5,18618

    nStates = 0;
    printf("Checking readElectionData() for a invalid file:\n");
    result = readElectionData("data/1829.csv", allStates, &nStates);
    if (result || nStates != 0) {
        printf("  Expected: false\n");
        return false;
    }

    return true; //modify this
}

bool test_minPVsSlow() {
    //----------------------------------------------------------------- 
    // TODO: Task 7 - write your own test case for minPopVoteAtLeast();
    //                make sure to test all components
    //-----------------------------------------------------------------

    State test[4] = {
        {"Alabama", "AL", 9, 1161642},
        {"Alaska", "AK", 3, 179766},
        {"Arizona", "AZ", 11, 1693664},
        {"Arkansas", "AR", 6, 609535}
    };

    MinInfo result;
    int reqEVs = 12;

    result = minPopVoteAtLeast(test, 4, 0, reqEVs);
    printf("Checking minPopVoteAtLeast() for minimum PV subset with required EVs:\n");
    if (!result.sufficientEVs || result.szSomeStates != 2 || result.subsetPVs != 670706) { 
        printf("  Expected: sufficientEVs = 1\n");
        printf("  Actual:   sufficientEVs = %d\n", result.sufficientEVs);
        return false;
    }

    // reqEVs = 30;
    // result = minPopVoteAtLeast(test, 4, 0, reqEVs);
    // printf("Checking minPopVoteAtLeast() for EVs greater than possible:\n");
    // if (result.sufficientEVs || result.szSomeStates != 0 || result.subsetPVs != 0) {
    //     printf("  Expected: sufficientEVs = 0\n");
    //     printf("  Actual:   sufficientEVs = %d\n", result.sufficientEVs);
    //     return false;
    // }

    // reqEVs = 0;
    // result = minPopVoteAtLeast(test, 4, 0, reqEVs);
    // printf("Checking minPopVoteAtLeast() for zero EV requirement:\n");
    // if (!result.sufficientEVs || result.szSomeStates != 0 || result.subsetPVs != 0) {
    //     printf("  Expected: sufficientEVs = 1\n");
    //     printf("  Actual:   sufficientEVs = %d\n", result.sufficientEVs);
    //     return false;
    // }

    return true; //modify this
}

bool test_minPVsFast() {
    //--------------------------------------------------------------------- 
    // TODO: Task 8 - write your own test case for minPopVoteAtLeastFast();
    //                make sure to test all components
    //---------------------------------------------------------------------
    State test[4] = {
        {"Alabama", "AL", 9, 1161642},
        {"Alaska", "AK", 3, 179766},
        {"Arizona", "AZ", 11, 1693664},
        {"Arkansas", "AR", 6, 609535}
    };

    MinInfo result;
    int reqEVs = 12;

    MinInfo** memo = (MinInfo**)malloc((5) * sizeof(MinInfo*));
    for (int i = 0; i <= 4; i++) {
        memo[i] = (MinInfo*)malloc((13) * sizeof(MinInfo));
        for (int j = 0; j <= 12; j++) {
            memo[i][j].subsetPVs = -1;
            memo[i][j].szSomeStates = 0;
            memo[i][j].sufficientEVs = false;
        }
    }

    result = minPopVoteAtLeastFast(test, 4, 0, reqEVs, memo);
    printf("Checking minPopVoteAtLeastFast() for minimum PV subset with required EVs:\n");
    if (!result.sufficientEVs || result.szSomeStates != 2 || result.subsetPVs != 670706) { 
        printf("  Expected: sufficientEVs = 1\n");
        printf("  Actual:   sufficientEVs = %d\n", result.sufficientEVs);
        return false;
    }

    // reqEVs = 30;
    // result = minPopVoteAtLeastFast(test, 4, 0, reqEVs, memo);
    // printf("Checking minPopVoteAtLeastFast() for EVs greater than possible:\n");
    // if (result.sufficientEVs) {
    //     printf("  Expected: sufficientEVs = 0\n");
    //     return false;
    // }

    // reqEVs = 0;
    // result = minPopVoteAtLeastFast(test, 4, 0, reqEVs, memo);
    // printf("Checking minPopVoteAtLeastFast() for zero EV requirement:\n");
    // if (!result.sufficientEVs) {
    //     printf("  Expected: sufficientEVs = 1\n");
    //     printf("  Actual:   sufficientEVs = %d\n", result.sufficientEVs);
    //     return false;
    // }

    for (int i = 0; i <= 4; i++) {
        free(memo[i]);
    }
    free(memo);
    return true; //modify this
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
