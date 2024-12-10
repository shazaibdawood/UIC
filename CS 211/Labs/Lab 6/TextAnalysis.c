#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "TextAnalysis.h"


// countWords() should open a file with name [filename]
//      and count the number of words in the file.
//      For our purposes here, a "word" is ANY set of 
//      characters that falls between two whitespaces 
//      (or tabs, or newlines, etc.). 
//      Return the word count. 
//      If the file does not exist, return -1;
//      Exs:    "this is a test" contains 4 words
//              "here is a star *" contains 5 words
//              "CS 211 ! Fall 2023 !" contains 6 words

int countWords(char filename[]) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        return -1;
    }
    int counter = 0;
    char character;
    int word = 0;
    while ((character = fgetc(file)) != EOF) {
        if (isspace(character)) {
            if (word) {
                counter++;
                word = 0; 
            }
        } else {
            word = 1;
        }
    }
    if (word) {
        counter++;
    }
    fclose(file);
    return counter;
}


// readWordList() should open a file with name [filename]
//      that contains [sz] "words" as defined in countWords()
//      and generate a heap-allocated array of C-strings to 
//      store all words from the file, in order, 
//      where each C-string in the array is individually 
//      heap-allocated with exactly the memory space needed 
//      to store the characters (these are null-terminating 
//      strings, so make sure there is one extra space for the 
//      null character). In practice, allocate an array of pointers, 
//      where each element points to a characer array (i.e C-string)
//      that is perfectly heap-allocated. Since we are building an 
//      array of pointers, the returned value (i.e. the array of 
//      C-strings) is a pointer to a pointer to a char (i.e. char**).
//      If the file does not exist, return NULL;
//      IMPORTANT: all words must be analyzed, BEFORE being added to the
//      word list, to ensure they do NOT end in non-alpha characters
//      exs:    "happy!" is added to the word list as "happy"
//              "CS211" is added to the word list as "CS"
//              "X-ray" is added to the word list as "X-ray"
//              "@2023" is added to the word list as "" (null char ONLY)
char** readWordList(char filename[], int sz) {
    
    // TODO: write the readWordList() function here
FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    char** words = (char**)malloc(sz * sizeof(char*));
    if (words == NULL) {
        fclose(file);
        return NULL; 
    }
    char word[100];  
    int counter = 0;  
    while (counter < sz && fscanf(file, "%99s", word) != EOF) {
        int len = strlen(word);
        while (len > 0 && !isalpha(word[len - 1])) {
            word[len - 1] = '\0';
            len--;
        }
        words[counter] = (char*)malloc((len + 1) * sizeof(char));

        if (words[counter] == NULL) {
            for (int i = 0; i < counter; i++) {
                free(words[i]);
            }
            free(words);
            fclose(file);
            return NULL;
        }

        strcpy(words[counter], word);
        counter++;
    }

    fclose(file);

    return words; //modify this
}


// wordListStats() should analyze the word list [allWords]
//      that contains [counter] C-strings and calculate 
//      the total number of characters in all of the words, 
//      returned using passed-by-pointer variable [charCount],
//      and find the longest word, returned as [longWord].
//      If multiple words tie for the longest word, [longWord] 
//      should be set to the earliest long word in the file 
void wordListStats(char** allWords, int counter, int* charCount, char* longWord) {
    *charCount = 0;
    strcpy(longWord, allWords[0]);
    for (int i = 0; i < counter; i++) {
        *charCount += strlen(allWords[i]);
        if (strlen(allWords[i]) > strlen(longWord)) {
            strcpy(longWord, allWords[i]);
        }
    }

}


// setFilenameW() should generate [filenameW], which is a filename that 
//      is built from [filenameR] and [wordLength], as follows:
//        - start with [filenameR]; assume it ends in ".txt"
//        - insert "_WordLength#" before ".txt"; "#" set by [wordLength]
//      ex: filenameR = "Hamlet.txt", wordLength = 5,
//              =>  filenameW = "Hamlet_WordLength5.txt"
void setFilenameW(char* filenameW, char* filenameR, int wordLength) {

    int length = strlen(filenameR);
    int shorten = length - 4;  
    strncpy(filenameW, filenameR, shorten);
    filenameW[shorten] = '\0';
    char word[20];  
    sprintf(word, "_WordLength%d", wordLength);
    strcat(filenameW, word);
    strcat(filenameW, ".txt");

}


// writeSomeWords() should generate a file with name [filenameW], 
//      and write to the file only words of length [wordLength]
//      that are found in the word list [allWords], which is an 
//      array of [numWords] C-strings. 
//      If the word list contains no words of length [wordLength],
//      then an empty file should be created.
//      The resulting file should have one word per line, in the 
//      order the words appear in the word list. Duplicate words in 
//      the word list should also be duplicated in the written file.
//      Return the number of words written to the new file.
//ex: [filenameW] = "test_WordLength4.txt"
//    [allWords] = {"this", "is", "a", "test", "a", "test", "of", "wits"}
//    [numWords] = 6
//    [wordLength] = 4
//          => test_WordLength4.txt should contain
//                  this
//                  test
//                  test
//                  wits
int writeSomeWords(char filenameW[], char** allWords, int numWords, int wordLength) {

    // TODO: write the writeSomeWords() function here

    FILE *file = fopen(filenameW, "w");
    if (file == NULL) {
        return -1;
    }
    int counter = 0;
    for (int i = 0; i < numWords; i++) {
        if (strlen(allWords[i]) == wordLength) {
            fprintf(file, "%s\n", allWords[i]);
            counter++;
        }
    }
    fclose(file);
    return counter; //modify this
}


// freeWords() should free all dynamic memory allocated for the word
//      list [allWords], which is an array of [counter] C-strings,
//      where each C-string was previously heap-allocated, in addition
//      to the array [allWords] being previously heap-allocated
void freeWords(char** allWords, int wordCount) {
    for (int i = 0; i < wordCount; i++) {
        free(allWords[i]); 
    }
    free(allWords);

}
