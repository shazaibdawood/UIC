#include "lab1.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int numWordsIn(const string& sentence) {
  istringstream ss(sentence);
  string s;
  int counter = 0;
  while (ss >> s) counter++;
  return counter;
  // if (sentence.length() == 0) return 0;

  // size_t space = sentence.find(' ');
  // int counter = 1;
  // if (space == string::npos) {
  //   return 1;
  // } else {
  //   while (space < sentence.length()) {
  //     space = sentence.find(' ', space + 1);
  //     while (!isalnum(sentence[space])) {
  //       space++;
  //     }
  //     counter++;
  //   }
  // }
  // return counter;
}

int main() {
  // This section gets a from standard input. We will talk about input on
  // Friday.
  string input_line;
  cout << "Enter a sentence: " << endl;
  getline(cin, input_line);

  cout << numWordsIn(input_line) << endl;
  return 0;
}
