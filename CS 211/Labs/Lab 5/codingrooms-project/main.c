#include <stdio.h>
//DO NOT #include the string.h library here

void strMystery1(char* str1, char* str2) {

    // TODO: first identify what string.h function is needed in main() 
    //       and then write your own version of it here in strMystery1()
    //strcat()
 
    char* pStr = str1;
    while (*pStr != '\0') {
        pStr++;
    }
    int length = pStr - str1;

    str1 += length;

    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++; 
    }
    *str1 = '\0';
}

void strMystery2(char* str1, char* str2) {
    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++; 
    }
    *str1 = '\0';
}

int strMystery3(char* str1, char* str2) {

    // TODO: first identify what string.h function is needed in main() 
    //       and then write your own version of it here in strMystery3()
    // strcmp()
    while(*str2 != '\0' || *str1 != '\0'){
        if(*str1 == *str2){
            str1++;
            str2++;
        }
        else{
            return *str1 - *str2;
        }
    }
    
    return 0; //modify this

}

int strMystery4(char* str) {
    char* pStr = str;
    while (*pStr != '\0') {
        pStr++;
    }
    return pStr - str;
}

// TODO: replace the calls to strlen() & strcmp() with 
//       calls to one of the strMystery#() functions
void printStuff(char* str1, char* str2) {
    printf("The 1st string is: %s\n",str1);
    printf("The 2nd string is: %s\n",str2);
    printf("The lengths of the strings are: %d and %d\n",(int)strMystery4(str1),(int)strMystery4(str2));
    printf("These two strings are ");
    if (strMystery3(str1,str2) != 0) {
        printf("NOT ");
    }
    printf("the same.\n\n"); 
}

int main() {
    // TODO: replace the calls to strcpy() & strcat() with 
    //       calls to one of the strMystery#() functions
   
    char testStr[20] = "this is a test";
    char aResStr[30];
    strMystery2(aResStr, testStr); 
    printStuff(testStr, aResStr);
    
    aResStr[10] = aResStr[10] + 6; 
    printStuff(testStr, aResStr);

    strMystery2(aResStr, testStr); 
    strMystery1(aResStr," of wits");
    printStuff(testStr, aResStr);

    return 0;
}
