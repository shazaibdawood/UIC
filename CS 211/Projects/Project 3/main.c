// Shazaib Dawood
// CS 211 4PM 
// Fall 2024 
// UIC
// Build a ladder of words using a dynamic array of c strings


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int strCmpCnt(char* word1, char* word2) {
//-------------------------------------------------------------------
// TODO - Task I: write the strCmpCnt() function, which returns the
//                count of character differences between two words 
//                (i.e. strings); include the extra characters in the 
//                longer word if the strings have different lengths
// Exs: word1 = magic, word2 = magic, returns 0
//      word1 = wands, word2 = wants, returns 1
//      word1 = magic, word2 = wands, returns 4
//      word1 = magic, word2 = mag, returns 2
//      word1 = magic, word2 = magicwand, returns 4
//      word1 = magic, word2 = darkmagic, returns 8
//-------------------------------------------------------------------
    // Find the smallest word
    // Add extra letter to the difference counter of both words are different sizes
    int differenceCounter = 0;
    int smallerWord = strlen(word1);
    if(strlen(word1) > strlen(word2)){
        smallerWord = strlen(word2);
        differenceCounter += (strlen(word1) - strlen(word2));
    }
    else if(strlen(word2) > strlen(word1)){
        smallerWord = strlen(word1);
        differenceCounter += (strlen(word2) - strlen(word1));
    }

    // Loop through every char in the word and count the number of differences
    // printf("%d ", differenceCounter); //Testing
    for(int i = 0; i < smallerWord; i++){
        if((*word1) != (*word2)){
            differenceCounter++;
        }
        // printf("%d ", differenceCounter); //Testing
        word1++;
        word2++;
    }
    
    return differenceCounter; //modify this
}


int strCmpInd(char* word1, char* word2) {
//-------------------------------------------------------------------
// TODO - Task II: write the strCmpInd() function, which returns the
//                 index of the character where two strings first 
//                 differ, & returns -1 if there are no differences
// Exs: word1 = magic, word2 = magic, returns -1
//      word1 = wands, word2 = wants, returns 3
//      word1 = magic, word2 = wands, returns 0
//      word1 = magic, word2 = mag, returns 3
//      word1 = magic, word2 = magicwand, returns 5
//      word1 = magic, word2 = darkmagic, returns 0
//-------------------------------------------------------------------
    // No differences
    if(strCmpCnt(word1, word2) == 0){
        return -1;
    }

    // find the larger word
    int largerWord = strlen(word1);
    if(strlen(word1) >= strlen(word2)){
        largerWord = strlen(word1);
    }
    else {
        largerWord = strlen(word2);
    }

    // loop through the word and return the first index where the chars are different
    for(int i = 0; i < largerWord; i++){
        if((*word1) != (*word2)){
            return i;
        }

        word1++;
        word2++;
    }
    return -1; //modify this
}


void appendWord(char*** pWords, int* pNumWords, int* pMaxWords, char* newWord) {
//---------------------------------------------------------------------
// TODO - Task III: write appendWord() function, which adds a new word
//      to a dynamic heap-allocated array of C-strings; heap-space must  
//      be allocated for the new word inside this function, then copy  
//      the chars from [newWord] to the newly allocated heap-space;
//      if adding a new word pushes *pNumWords greater than *pMaxWords, 
//      then realloate the *pWords array with double the capacity.
//      parameters: 
//          [char*** pWords] - array of C-strings passed-by-pointer
//              note: *pWords is an array of pointers
//                    **pWords is an array of chars
//                    ***pWords is a char  
//                    (*pWords)[0] is the 1st C-string in the array
//                    (*pWords)[1] is the 2nd C-string in the array
//                    (*pWords)[0][0] is 1st char of 1st C-string
//                    (*pWords)[1][2] is 3rd char of 2nd C-string
//                    etc.
//          [int* pNumWords] - current # of words in *pWords array
//               note: *pNumWords will increase by 1 here, 
//                     so it is passed-by-pointer
//          [int* pMaxWords] - current capacity of *pWords array
//               note: *pMaxWords may increase by x2 here, 
//                     so it is passed-by-pointer
//          [char* newWord] - C-string word to be added to *pWords
//               note: [newWord] is a C-string, naturally a pointer
//---------------------------------------------------------------------
    // If the current number of words equal the maximum capacity then malloc a new pwords with double the capacity
    // copy the old pwords into the new pwords
    // Reallocate double the max words if the current number of words = maximum number of words
    if((*pNumWords) == (*pMaxWords)){
        (*pMaxWords) *= 2;

        *pWords = (char**)realloc(*pWords, (*pMaxWords) * sizeof(char*));
    }

    // copy the new word into pword at the index pNumWords
    // increment pNumWords
    (*pWords)[*pNumWords] = (char*)malloc(sizeof(char) * (1 + strlen(newWord)));
    strcpy((*pWords)[*pNumWords], newWord);
    (*pNumWords)++;
}


int linSearchForWord(char** words, int numWords, char* findWord) { 
//-------------------------------------------------------------------
// TODO - Task V: write the linSearchForWord() function that returns 
//      the index in the [words] C-string array where a match to the 
//      C-string [findWord] is found, using a linear search; 
//      return -99 if [findWord] is NOT found in [words] array;
//      note: [words] is an array of pointers to [numWords] C-strings 
//-------------------------------------------------------------------

    // Go through all the words in the words array
    // return the index of the word if it is found
    // if it is not in the array then return -99
    for(int i = 0; i < numWords; i++){
        // char* tempWord[100];
        // strcpy(tempWord, words[i]);
        if(strcmp(words[i], findWord) == 0){
            return i;
        }
    }

    return -99; // modify this
}


bool checkForValidWord(char** words, int numWords, int wordLen, char** ladder, int ladderHeight, char* aWord) {
//-------------------------------------------------------------------
// TODO - Task VI: write the checkForValidWord() function, which checks 
//      if [aWord] is valid for the next word in the word ladder;
//
//      return TRUE for the following cases:
//        - [aWord] is "DONE" beacuse the user wants to stop;
//              this case takes highest precedence;
//              before returning TRUE, first print: 
//                  "Stopping with an incomplete word ladder..."
//        - [aWord] is valid and will be added to the word ladder
//              before returning TRUE, first print: 
//                  "Entered word is valid and will be added to the word ladder."
//
//      return FALSE for the following cases
//      (precedence for invalidity measures follows the order given here):
//        - [aWord] is invalid because it has the wrong word length;
//              before returning FALSE, first print: 
//                  "Entered word does NOT have the correct length. Try again..."
//        - [aWord] is invalid because it is not in the words array,  
//              i.e. not in the dictionary;
//              before returning FALSE, first print: 
//                  "Entered word NOT in dictionary. Try again..."
//        - [aWord] is invalid because it is NOT a single-char 
//              difference from the previous word in the ladder; 
//              e.g. previous word is "code" and [aWord] is "cave";
//              e.g. previous word is "code" and [aWord] is "code";
//              before returning FALSE, first print: 
//                  "Entered word is NOT a one-character change from the previous word. Try again..."
//
//      [words] is an array of [numWords] C-strings that contains all 
//              words in the dictionary of word length [wordLen]
//      [ladder] is an array of [ladderHeight] C-strings that 
//              represents an incomplete word ladder
//      [aWord] is a C-string that must be checked for validity here
//
//  HINT: call linSearchWord(), strCmpCnt(), & string.h function(s)
//-------------------------------------------------------------------

    // First check if the word is done
    // then check if the length matches wordLen
    // then check if the word is in the words array
    // then check if there is only 1 character difference between it and the last word in the ladder
    // otherwise return true
    if(strcmp("DONE", aWord) == 0){
        printf("Stopping with an incomplete word ladder...\n");
        return true;
    }
    else if(strlen(aWord) != wordLen){
        printf("Entered word does NOT have the correct length. Try again...\n");
        return false;
    }
    else if(linSearchForWord(words, numWords, aWord) == -99){
        printf("Entered word NOT in dictionary. Try again...\n");
        return false;
    }
    else if(strCmpCnt(aWord, ladder[ladderHeight - 1]) != 1){
        printf("Entered word is NOT a one-character change from the previous word. Try again...\n");
        return false;
    }
    else{
        printf("Entered word is valid and will be added to the word ladder.\n");
        return true; // modify this
    }
    
}


bool isLadderComplete(char** ladderWords, int height, char* finalWord) {
//-------------------------------------------------------------------
// TODO - Task VII: write the isLadderComplete() Boolean function, 
//      which should simply check for a completed word ladder, i.e.
//      return true if the final word in [ladderWords] is a match to 
//      [finalWord]; otherwise, return false; the number of words in
//      the word ladder is [height]
//-------------------------------------------------------------------
    // Check if the last word in the ladder is the final word
    if(strcmp(ladderWords[height - 1], finalWord) == 0){
        return true;
    }
    return false; // modify this
}


void displayIncompleteLadder(char** ladderWords, int height) {
//-------------------------------------------------------------------
// TODO - Task IX: write the displayIncompleteLadder() function, 
//      which should display the C-strings in the [ladderWords] 
//      array with the first word at the bottom of the ladder, and 
//      each successive C-string one rung higher on the ladder. 
//      The ladder [height] is the number of words it contains.  
//      To signify the ladder as incomplete, display three lines of  
//      "..." at the top of the ladder. The ladder must be displayed 
//      with an indentation of two whitespaces on every line;
//      Ex: if the start word is "data" and final word is "code" and
//          the incomplete ladder is data->date->gate->gave, then the
//          output display should be as follows (where the quotation  
//          marks are NOT a part of the actual display):
//              "  ..."
//              "  ..."
//              "  ..."
//              "  gave"
//              "  gate"
//              "  date"
//              "  data" 
//-------------------------------------------------------------------

for(int i = 0; i < 3; i++){
    printf("  ...\n");
}

for(int i = height - 1; i >= 0; i--){
    printf("  %s\n", ladderWords[i]);
}

}


void displayCompleteLadder(char** ladderWords, int height) {
//-------------------------------------------------------------------
// TODO - Task X: write the displayCompleteLadder() function, 
//      which should display the C-strings in the [ladderWords] array 
//      with the first word at the bottom of the ladder, and each 
//      successive C-string one rung higher on the ladder. 
//      The ladder [height] is the number of words it contains.  
//      In between each ladder rung, display the symbol '^' to 
//      signify the character that changes between the two rungs of 
//      the ladder. The ladder should be displayed with an indentation 
//      of two whitespaces to the left of every word;
//
//      HINT: call strCmpInd() here
//
//      Ex: if the start word is "data" and final word is "code" 
//          then the output display for a complete ladder should be  
//          as follows (where the quotation marks are NOT a part of  
//          the actual display):
//              "  code"
//              "    ^ "
//              "  cove"
//              "   ^  "
//              "  cave"
//              "  ^   "
//              "  gave"
//              "    ^ "
//              "  gate"
//              "  ^   "
//              "  date"
//              "     ^"
//              "  data" 
//-------------------------------------------------------------------

// go through the ladder backwords and print out each word
// after each word use strCmpInd() to find where the words are different
// print ^ where it is different and a space where it isn't
for(int i = height - 1; i >= 0; i--){
    printf("  %s\n", ladderWords[i]);
    int numChar = strlen(ladderWords[i]);

    if(i > 0){
        printf("  ");

        int index = strCmpInd(ladderWords[i], ladderWords[i - 1]);
        for(int j = 0; j < numChar; j++){
            if(j == index){
                printf("^");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
}


int main(int argc, char* argv[]) {
    // Testing
    // printf("%d\n", strCmpInd("magic", "magic"));
    // printf("%d\n", strCmpInd("wands", "wants"));
    // printf("%d\n", strCmpInd("magic", "wands"));
    // printf("%d\n", strCmpInd("magic", "mag"));
    // printf("%d\n", strCmpInd("magic", "magicwand"));
    // printf("%d\n", strCmpInd("magic", "darkmagic"));


    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0;
    int maxLadder = 1;
    char dict[100] = "notAfile";     
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid"; 

    //-------------------------------------------------------------------
    // TODO - Task XII: handle command-line arguments
    // command-line arguments:
    //  [-n wordLen] = sets word length for word ladder;
    //                 if [wordLen] is not a valid input 
    //                 (cannot be less than 2 or greater than 20),
    //                 or missing from command-line arguments, 
    //                 then let user set it using interactive user input
    // [-m maxLadder] = sets maximum word ladder height;
    //                  [maxLadder] must be at least 2;
    //                  if [maxLadder] is invalid or missing from 
    //                  command-line arguments, then let user set it 
    //                  using interactive user input
    // [-d dictFile] = sets dictionary file;
    //                 if [dictFile] is invalid (file not found) or 
    //                 missing from command-line arguments, then let
    //                 user set it using interactive user input
    // [-s startWord] = sets the starting word;
    //                  if [startWord] is invalid 
    //                  (not in dictionary or incorrect length) or 
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    // [-f finalWord] = sets the final word;
    //                  if [finalWord] is invalid  
    //                  (not in dictionary or incorrect length) or 
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    //-------------------------------------------------------------------


    printf("Interactively (re)setting invalid parameters:\n");
    
    // Loop through command line argument array and reset values accordingly
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-n") == 0 && i + 1 < argc){
            wordLen = atoi(argv[i + 1]);
        }
        else if(strcmp(argv[i], "-m") == 0 && i + 1 < argc){
            maxLadder = atoi(argv[i + 1]);
        }
        else if(strcmp(argv[i], "-d") == 0 && i + 1 < argc){
            strcpy(dict, argv[i + 1]);
        }
        else if(strcmp(argv[i], "-s") == 0 && i + 1 < argc){
            strcpy(startWord, argv[i + 1]);
        }
        else if(strcmp(argv[i], "-f") == 0 && i + 1 < argc){
            strcpy(finalWord, argv[i + 1]);
        }
    }

    // set word length using interactive user-input if necessary
    int numInputs = 1;
    while (numInputs > 0 && (wordLen < 2 || wordLen > 20)) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        numInputs = scanf("%d",&wordLen);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    // set max ladder height using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        numInputs = scanf("%d",&maxLadder);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");        
        return 0;
    }

    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    FILE* fileTry = fopen(dict,"r");
    numInputs = 1;
    while (numInputs > 0 && fileTry == NULL) {
        printf("Dictionary file %s not found...\n", dict);
        printf("Enter filename for dictionary: ");
        numInputs = scanf("%s", dict);
        printf("\n");
        fileTry = fopen(dict,"r");
    }
    fclose(fileTry);
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");        
        return 0;
    }
    
    // build the [words] array, a heap-allocated array of C-strings
    // where the words are a read-in from the dictionary file
    // and only those words of the desired length [wordLen] 

    int numWords = 0; // initially, no words in the array
    int maxWords = 4; // initially, capacity = 4

    char** words = (char**)malloc(maxWords*sizeof(char*));
    //-------------------------------------------------------------------
    // TODO - Task IV: file-read the word list from the dictionary file 
    //                 [dict], storing only words of length set by 
    //                 [wordLen] in [words], which is a dynamically 
    //                 growing heap-allocated array of C-strings:
    //                      - the word list should be a dynamic array of 
    //                        pointers, initially with capacity (i.e. 
    //                        maximum size) 4; the capacity doubles 
    //                        whenever more space is needed
    //                      - each element of the word list array should 
    //                        point to a heap-allocated C-string that 
    //                        can store a word containing exactly 
    //                        [wordLen] lower-case letters; don't forget
    //                        that there must be a single char at the 
    //                        end of the C-string for the null character
    //
    //                 HINT: open the file; loop to read words from the
    //                 file and check if the word has the correct length;
    //                 if so, add the word to the array using a call to 
    //                 appendWord(); lastly, close the file after all words 
    //                 have been scanned
    //-------------------------------------------------------------------
    
    // open the file for reading
    // readeach word into a temporary c string
    // if the word is the desired length, then add it to the words array
    // use the appendWord() function to auotmatically grow the array
    FILE* inFile = fopen(dict,"r");
    char tempWord[100];
    while((fscanf(inFile, "%s", tempWord) == 1)){
        if(strlen(tempWord) == wordLen){
            appendWord(&words, &numWords, &maxWords, tempWord);
        }
    }
    fclose(inFile);

    printf("The dictionary contains %d words of length %d.\n",numWords,wordLen);
    printf("Max size of the dynamic words array is %d.\n",maxWords);
    printf("\n");

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");

        if(words != NULL){
            for(int i = 0; i < numWords; i++){
                if(words[i] != NULL){
                    free(words[i]);
                }
            }
            free(words);
        }

        return -1;
    }

    // resetting start word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,startWord) < 0) {
        printf("Start word %s is not valid...\n", startWord);
        printf("Enter a valid start word: ");
        numInputs = scanf("%s", startWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        
        if(words != NULL){
            for(int i = 0; i < numWords; i++){
                if(words[i] != NULL){
                    free(words[i]);
                }
            }
            free(words);
        }
        
        return 0;
    }

    // resetting final word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,finalWord) < 0 ) {
        printf("Final word %s is not valid...\n", finalWord);
        printf("Enter a valid final word: ");
        numInputs = scanf("%s", finalWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        
        if(words != NULL){
            for(int i = 0; i < numWords; i++){
                if(words[i] != NULL){
                    free(words[i]);
                }
            }
            free(words);
        }
        
        return 0;
    }

    printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\n"); 

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);  
    
    // Allocating the word ladder for the maximum allowed height
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));

    int ladderHeight = 0; // initially, the ladder is empty
    
    // add the start word to the ladder, i.e. the "bottom rung"
    appendWord(&ladder,&ladderHeight,&maxLadder,startWord);
    
    char aWord[30] = "XYZ";
    printf("\n");

    // Let the user build a word ladder interactively & iteratively.
    // First, check that ladder is not too long AND not complete.
    //-------------------------------------------------------------------
    // TODO - Task VIII: modify the while loop condition such that the 
    //          word ladder building process continues only if ALL of  
    //          the following conditions are met:
    //              1. the ladder still has at least one available rung
    //                 before reaching the maximum allowed height
    //              2. the user is NOT attempting to stop the word ladder
    //                 building process, which occurs if the entered word 
    //                 [aWord] from the last iteration is "DONE"
    //              3. the ladder is still incomplete; i.e. the last word
    //                 added to ladder is not the final word; 
    //                 note: this should use a call to isLadderComplete() 
    //-------------------------------------------------------------------
    while (ladderHeight < maxLadder && strcmp(aWord, "DONE") != 0 && !isLadderComplete(ladder, ladderHeight, finalWord)) {   // modify this line 
        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        // Make sure the entered word is valid for the next ladder rung;
        // if not, repeatedly allow user to enter another word until one is valid
        while (!checkForValidWord(words, numWords, wordLen, ladder, ladderHeight, aWord)) {
            printf("Enter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
        }

        // add the entered word to the ladder (unless it is "DONE")
        if (strcmp(aWord,"DONE") != 0) {
            appendWord(&ladder,&ladderHeight,&maxLadder,aWord);
        }
        printf("\n");

    }
    

    // Check if the built word ladder is complete and 
    // display the word ladder appropriately. 
    if (isLadderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }
    
    
    //-------------------------------------------------------------------
    // TODO - Task XI: free all heap-allocated memory to avoid potential 
    //                 memory leaks. Since the word length for the word 
    //                 ladder is variable (i.e. set by a command-line 
    //                 argument or interactive user-input) any array
    //                 whose size depends on the word length should be
    //                 dynamically heap-allocated, and thus, must be
    //                 tracked and freed before program termination
    //-------------------------------------------------------------------
    if(ladder != NULL){
        for(int i = 0; i < ladderHeight; i++){
            if(ladder[i] != NULL){
                free(ladder[i]);
            }
        }
        free(ladder);
    }

    if(words != NULL){
        for(int i = 0; i < numWords; i++){
            if(words[i] != NULL){
                free(words[i]);
            }
        }
        free(words);
    }

    return 0;
}