#include <stdio.h>

#include "TextAnalysis.h"

int main() {
    printf("Welcome to the Text File Analyzer Application\n\n");
    printf("Enter the filename for text analysis:\n");
    char filename[30];
    scanf("%s",filename); 

    int numWords = countWords(filename);
    if (numWords < 0) {
        printf("%s not found. Terminating application...\n",filename);
        return -1;
    }
    char** allWords = readWordList(filename, numWords);

    int wordCnt = numWords;
    int charCnt = 0;
    char longWord[100] = "";
    
    wordListStats(allWords, numWords, &charCnt, longWord) ;
    printf("Statistics for %s:\n",filename);
    printf("  total word count: %d\n",wordCnt);
    printf("  total char count: %d\n",charCnt);
    printf("  avg. word length: %0.2lf\n",1.0 * charCnt / wordCnt);
    printf("  longest word: %s\n",longWord);

    int wrdLen;
    char filenameW[50] = "";
    printf("Find and save to file all words of length: \n");
    scanf("%d",&wrdLen);
    setFilenameW(filenameW,filename,wrdLen);
    int numW = writeSomeWords(filenameW,allWords,wordCnt,wrdLen);
    printf("%d words of length %d in %s written to %s \n",numW,wrdLen,filename,filenameW);

    freeWords(allWords,wordCnt);

    return 0;
}
