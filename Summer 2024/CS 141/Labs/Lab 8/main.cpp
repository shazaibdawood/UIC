/* Cipher Lab using C strings */

/* Running the program looks like:
    Enter some lower-case text: hello
    Shifting  0 gives: hello
    Shifting  1 gives: ifmmp
    Shifting  2 gives: jgnnq
    Shifting  3 gives: khoor
    Shifting  4 gives: lipps
    Shifting  5 gives: mjqqt
    Shifting  6 gives: nkrru
    Shifting  7 gives: olssv
    Shifting  8 gives: pmttw
    Shifting  9 gives: qnuux
    Shifting 10 gives: rovvy
    Shifting 11 gives: spwwz
    Shifting 12 gives: tqxxa
    Shifting 13 gives: uryyb
    Shifting 14 gives: vszzc
    Shifting 15 gives: wtaad
    Shifting 16 gives: xubbe
    Shifting 17 gives: yvccf
    Shifting 18 gives: zwddg
    Shifting 19 gives: axeeh
    Shifting 20 gives: byffi
    Shifting 21 gives: czggj
    Shifting 22 gives: dahhk
    Shifting 23 gives: ebiil
    Shifting 24 gives: fcjjm
    Shifting 25 gives: gdkkn
 */

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>

using namespace std;

// Global constants
const int MaxWordSize = 81;     // 80 characters + 1 for NULL


// Given an array of characters and a shift value:
//    shift each character in the original text by some amount,
//    storing the result into the shiftedText array.
// Remember: Wrap around at the end of the alphabet.
// *** In the line below you must supply the function 
//     return type and the parameter(s) ***
void shiftTheText(char x[], int z, char y[])
{
   // Loop through each character in the C string, startingText
   // When the character is an alphabetic character, 
   //    shift it by adding the shift value. 
   // Then store the resulting character in its proper spot
   //       in the shiftedText C string.
   for(int i = 0; i < strlen(x); i++)
   {
      if(!isalpha(x[i]))
      {
         y[i] = x[i];
         continue;
      }
      
      char temp = x[i] + z;
      if(!isalpha(temp))
      {
         temp -= 26;
      }
      
      y[i] = temp;
   }
}


int main()
{
    // Initialize the variables
    char startingText[ MaxWordSize];
    char shiftedText[ MaxWordSize];

    cout << "Enter some lower-case text: ";
    cin >> startingText;
   //  int shiftValue = 6;
   //  shiftTheText(startingText, shiftValue, shiftedText);
   //  cout << endl;
   //  cout << startingText << endl;
   //  cout << shiftedText << endl;

    for(int shiftValue = 0; shiftValue < 26; shiftValue++) {
       // In the function call below you need to pass the starting text array, the shift value, and the shifted text array.
       shiftTheText(startingText, shiftValue, shiftedText);
       cout << "Shifting " << setw( 2) << shiftValue << " gives: " << shiftedText << endl;
    }
 
    return 0;   // Keep C++ happy

}// end main()