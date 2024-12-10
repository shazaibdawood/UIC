/* template for .h file */

/* put any #define statements here */
#ifndef TEXTANALYSIS_H_
#define TEXTANALYSIS_H_

/* put any structure declarations here */

/* list any needed function prototypes here */
int countWords(char filename[]);
char** readWordList(char filename[], int sz);
void wordListStats(char** allWords, int wordCount, int* charCount, char* longWord);
void setFilenameW(char* filenameW, char* filenameR, int wordLength);
int writeSomeWords(char filenameW[], char** allWords, int numWords, int wordLength);
void freeWords(char** allWords, int wordCount);

#endif