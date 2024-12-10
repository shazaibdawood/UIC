#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "TextAnalysis.h"

// test_countWords() tests countWords() for three cases
//   case 1: non-existant file should return -1
//   case 2: FrostRoad.txt contains 151 words 
//        (check with UNIX command >> wc FrostRoad.txt)
//   case 3: GreenEggsAndHam.txt contains 809 words 
//        (check with UNIX command >> wc GreenEggsAndHam.txt)
bool test_countWords() {
    bool res = true;
    int n = countWords("hello.txt");
    if (n != -1) {
        printf("    for hello.txt,\n");
        printf("    countWords() returns incorrect value\n");
        printf("    expected = -1, actual = %d\n",n);
        res = false;
    }

    n = countWords("FrostRoad.txt");
    if (n != 151) {
        printf("    for FrostRoad.txt,\n");
        printf("    countWords() returns incorrect value\n");
        printf("    expected = 151, actual = %d\n",n);
        res = false;
    }
    
    n = countWords("GreenEggsAndHam.txt");
    if (n != 809) {
        printf("    for GreenEggsAndHam.txt,\n");
        printf("    countWords() returns incorrect value\n");
        printf("    expected = 809, actual = %d\n",n);
        res = false;
    }
    return res;
}

// test_readWordList() tests readWordList() 
//    - word list created, not NULL
//    - check a few specific words; some requiring removal
//      of non-alpha characters from the back; expected
//      words determined from manual inspection of file
//   file 1: FrostRoad.txt
//   file 2: MLK-Dream.txt
bool test_readWordList() {
    bool res = true;
    char** allWords = readWordList("FrostRoad.txt", 151);
    if (allWords == NULL) {
        printf("    for FrostRoad.txt,\n");
        printf("    readWordList() returns NULL\n");
        res = false;
    }
    if (strcmp(allWords[0],"The") != 0) {
        printf("    for FrostRoad.txt,\n");
        printf("    readWordList() returns incorrect basic word in word list\n");
        printf("    word at index 0; expected {The}, actual {%s}\n",allWords[0]);
        res = false;
    }
    if (strcmp(allWords[7],"Two") != 0) {
        printf("    for FrostRoad.txt,\n");
        printf("    readWordList() returns incorrect word in word list\n");
        printf("    word at index 7; expected {Two}, actual {%s}\n",allWords[7]);
        res = false;
    }
    if (strcmp(allWords[13],"wood") != 0) {
        printf("    for FrostRoad.txt,\n");
        printf("    readWordList() returns incorrect word in word list\n");
        printf("    word at index 13; expected {wood}, actual {%s}\n",allWords[13]);
        res = false;
    }
    if (strcmp(allWords[150],"difference") != 0) {
        printf("    for FrostRoad.txt,\n");
        printf("    readWordList() returns incorrect word in word list\n");
        printf("    word at index 150; expected {difference}, actual {%s}\n",allWords[150]);
        res = false;
    }

    allWords = readWordList("MLK-Dream.txt", 1663);
    if (allWords == NULL) {
        printf("    for MLK-Dream.txt,\n");
        printf("    readWordList() returns NULL\n");
        return 0;
    }
    if (strcmp(allWords[0],"Dr") != 0) {
        printf("    for MLK-Dream.txt,\n");
        printf("    readWordList() returns incorrect word in word list\n");
        printf("    word at index 0; expected {Dr}, actual {%s}\n",allWords[0]);
        return 0;
    }
    if (strcmp(allWords[307],"funds") != 0) {
        printf("    for MLK-Dream.txt,\n");
        printf("    readWordList() returns incorrect word in word list\n");
        printf("    word at index 307; expected {funds}, actual {%s}\n",allWords[307]);
        return 0;
    }
    if (strcmp(allWords[778],"satisfied") != 0) {
        printf("    for MLK-Dream.txt,\n");
        printf("    readWordList() returns incorrect word in word list\n");
        printf("    word at index 778; expected {satisfied}, actual {%s}\n",allWords[778]);
        return 0;
    }

    return res;
}

// TODO: add a function here to test another one of the 
//       functions in TextAnalysis.c
bool test_wordListStats(){
    bool res = true;
    int numWords = countWords("GreenEggsAndHam.txt");
    char** allWords = readWordList("GreenEggsAndHam.txt", numWords);
    int charCnt = 0;
    char longWord[100] = "";
    wordListStats(allWords, numWords, &charCnt, longWord) ;
    if(strcmp("anywhere", longWord) != 0){
        res = false;
        printf("Incorrect Long Word\n");
    }
    if(charCnt != 2433){
        res = false;
        printf("incorrect char count\n");
    }

    return res;
}

int main() {
    printf("Welcome to the Text File Analyzer Testing Suite\n\n");
    
    printf("Testing countWords():\n");
    if (test_countWords()) {
        printf("  All tests PASSED - countWords() functioning correctly.\n");
    } else {
        printf("  One or more test FAILED - countWords() NOT functioning correctly.\n");
    }
    
    printf("Testing readWordList():\n");
    if (test_readWordList()) {
        printf("  All tests PASSED - readWordList() functioning correctly.\n");
    } else {
        printf("  One or more test FAILED - readWordList() NOT functioning correctly.\n");
    }
    
    // TODO: add code here to call the additional test case 
    //       you wrote, with helpful print statements 
    //       similar to those above
    printf("Testing wordListStats():\n");
    if (test_wordListStats()) {
        printf("  All tests PASSED - wordListStats() functioning correctly.\n");
    } else {
        printf("  One or more test FAILED - wordListStats() NOT functioning correctly.\n");
    }

    return 0;
}
