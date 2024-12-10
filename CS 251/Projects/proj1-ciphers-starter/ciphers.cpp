#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/caesar_dec.h"
#include "include/caesar_enc.h"
#include "include/subst_dec.h"
#include "include/subst_enc.h"
#include "utils.h"

using namespace std;

// Initialize random number generator in .cpp file for ODR reasons
std::mt19937 Random::rng;

/**
 * Print instructions for using the program.
 */
void printMenu() {
  cout << "Ciphers Menu" << endl;
  cout << "------------" << endl;
  cout << "C - Encrypt with Caesar Cipher" << endl;
  cout << "D - Decrypt Caesar Cipher" << endl;
  cout << "E - Compute English-ness Score" << endl;
  cout << "A - Apply Random Substitution Cipher" << endl;
  cout << "S - Decrypt Substitution Cipher from Console" << endl;
  cout << "F - Decrypt Substitution Cipher from File" << endl;
  cout << "R - Set Random Seed for Testing" << endl;
  cout << "X - Exit Program" << endl;
}

vector<char> decryptSubstCipher(const QuadgramScorer& scorer,
                                const string& ciphertext);

int main() {
    vector<string> dictionary;
  ifstream inFS;
  ofstream outFS;
  string currWord;
  inFS.open("dictionary.txt");
  if (!inFS.is_open()) {
    cout << "dictionary.txt is not open" << endl;
  }
  while (!inFS.eof()) {
    inFS >> currWord;
    dictionary.push_back(currWord);
  }
  inFS.close();

  vector<string> quadgrams;
  vector<int> counts;

  inFS.open("english_quadgrams.txt");
  if (!inFS.is_open()) {
    cout << "english_quadgrams.txt is not open" << endl;
  }

  string quadgramsData;
  while (!inFS.eof()) {
    inFS >> quadgramsData;
    int commaIndex = quadgramsData.find(',');
    string quadgram = quadgramsData.substr(0, commaIndex);
    int count = stoi(quadgramsData.substr(commaIndex + 1));

    quadgrams.push_back(quadgram);
    counts.push_back(count);
  }
  inFS.close();

  QuadgramScorer scorer(quadgrams, counts);

  Random::seed(time(NULL));
  string command;

  cout << "Welcome to Ciphers!" << endl;
  cout << "-------------------" << endl;
  cout << endl;

  do {
    printMenu();
    cout << endl << "Enter a command (case does not matter): ";

    // Use getline for all user input to avoid needing to handle
    // input buffer issues relating to using both >> and getline
    getline(cin, command);
    cout << endl;

    if (command == "R" || command == "r") {
      string seed_str;
      cout << "Enter a non-negative integer to seed the random number "
              "generator: ";
      getline(cin, seed_str);
      Random::seed(stoi(seed_str));
    } else if (command == "C" || command == "c") {
      runCaesarEncrypt();
    } else if (command == "D" || command == "d") {
      runCaesarDecrypt(dictionary);
    } else if (command == "A" || command == "a") {
      applyRandSubstCipherCommand();
    } else if (command == "E" || command == "e") {
      computeEnglishnessCommand(scorer);
    } else if (command == "S" || command == "s") {
      decryptSubstCipherCommand(scorer);
    } else if (command == "F" || command == "f") {
      string inputFileName, outputFilename;

      cout << "Enter filename with text to substitution-cipher decrypt: "
           << endl;
      getline(cin, inputFileName);

      cout << "Enter filename to write results to: " << endl;
      getline(cin, outputFilename);

      inFS.open(inputFileName);
      if (!inFS.is_open()) {
        cout << inputFileName << " is not open" << endl;
      }

      outFS.open(outputFilename);
      if (!outFS.is_open()) {
        cout << outputFilename << " is not open" << endl;
      }

      string findCipher;
      getline(inFS, findCipher);
      string tempstr;
      while (!inFS.eof()) {
        getline(inFS, tempstr);
        findCipher = findCipher + "\n" + tempstr;
      }

      string cleaned = clean(findCipher);
      // cout << cleaned << endl;
      vector<char> key = decryptSubstCipher(scorer, cleaned);
      string plaintext = applySubstCipher(key, findCipher);
      // cout << plaintext << endl;

      outFS << plaintext;

      inFS.close();
      outFS.close();
    }

    cout << endl;

  } while (!(command == "x" || command == "X") && !cin.eof());

  // cout << rot('A', 1) << endl;
  // cout << rot("A B C D", 27) << endl;

  return 0;
}

// "#pragma region" and "#pragma endregion" group related functions in this file
// to tell VSCode that these are "foldable". You might have noticed the little
// down arrow next to functions or loops, and that you can click it to collapse
// those bodies. This lets us do the same thing for arbitrary chunks!
#pragma region CaesarEnc

char rot(char c, int amount) {
  int newCIndex = (ALPHABET.find(c) + amount) % 26;
  char rotC = ALPHABET.at(newCIndex);

  return rotC;
}

string rot(const string& line, int amount) {
  char c;
  string shiftedLine = "";
  for (int i = 0; i < line.size(); i++) {
    c = line.at(i);
    if (isspace(c)) {
      shiftedLine += c;
      continue;
    } else if (isalpha(c)) {
      char rotatedC = rot(toupper(c), amount);
      shiftedLine += rotatedC;
    }
  }
  return shiftedLine;
}

void runCaesarEncrypt() {
  string plainText;
  string strNumRot;
  string cipherText;
  int numRot;

  cout << "Enter the text to Caesar encrypt: " << endl;
  getline(cin, plainText);

  cout << "Enter the number of characters to rotate by: " << endl;
  getline(cin, strNumRot);
  numRot = stoi(strNumRot);

  cipherText = rot(plainText, numRot);
  cout << cipherText << endl;
}

#pragma endregion CaesarEnc

#pragma region CaesarDec

void rot(vector<string>& strings, int amount) {
  for (int i = 0; i < strings.size(); i++) {
    string tempstr = rot(strings.at(i), amount);
    strings.at(i) = tempstr;
  }
}

string clean(const string& s) {
  string cleanedString = "";
  char cleanedChar;
  for (int i = 0; i < s.size(); i++) {
    cleanedChar = s.at(i);
    if (isalpha(cleanedChar)) {
      cleanedString += toupper(cleanedChar);
    }
  }
  return cleanedString;
}

vector<string> splitBySpaces(const string& s) {
  vector<string> sentence;
  int spaceIndex = 0;
  string tempstr = s;

  while (spaceIndex < s.size()) {
    spaceIndex = tempstr.find(' ');
    if (spaceIndex == string::npos) {
      tempstr = clean(tempstr);
      if (tempstr.size() > 0) {
        sentence.push_back(tempstr);
      }
      spaceIndex = s.size();
    } else {
      string temp = tempstr.substr(0, spaceIndex + 1);
      tempstr = tempstr.substr(spaceIndex + 1);
      temp = clean(temp);
      if (temp.size() > 0) {
        sentence.push_back(temp);
      }
    }
  }
  return sentence;
}

string joinWithSpaces(const vector<string>& words) {
  string joined = "";
  for (int i = 0; i < words.size(); i++) {
    joined = joined + words.at(i) + " ";
  }
  if (joined.size() > 0) {
    joined.pop_back();
  }
  return joined;
}

int numWordsIn(const vector<string>& words, const vector<string>& dict) {
  int numWords = 0;
  for (int i = 0; i < words.size(); i++) {
    for (int j = 0; j < dict.size(); j++) {
      if (words.at(i) == dict.at(j)) {
        numWords++;
        break;
      }
    }
  }
  return numWords;
}

string uppercaseAndRemoveNonLetters(string x) {
  string y = "";
  char tempC;
  for (int i = 0; i < x.size(); i++) {
    tempC = x.at(i);
    if (!isalpha(tempC)) {
      continue;
    }
    tempC = toupper(tempC);
    y += tempC;
  }
  return y;
}

int findWord(string word, const vector<string>& dict) {
  for (int i = 0; i < dict.size(); i++) {
    if (dict.at(i) == word) {
      return i;
    }
  }
  return dict.size();
}

void runCaesarDecrypt(const vector<string>& dict) {
  string cipherText;

  cout << "Enter the text to Caesar decrypt: " << endl;
  getline(cin, cipherText);

  vector<string> sentence = splitBySpaces(cipherText);

  int cipherFound = 26;

  for (int i = 0; i < 25; i++) {
    vector<string> shiftedSentence = sentence;
    rot(shiftedSentence, i);

    int numWords = numWordsIn(shiftedSentence, dict);
    // cout << numWords << endl;
    if (numWords > shiftedSentence.size() / 2) {
      cipherFound = i;
      cout << joinWithSpaces(shiftedSentence) << endl;
    }
  }
  if (cipherFound == 26) {
    cout << "No good decryptions found" << endl;
  } else {
  }
}

#pragma endregion CaesarDec

#pragma region SubstEnc

// int findCipherIndex(const vector<char>& cipher, const char c) {
//   int cipherIndex = 0;
//   for (int i = 0; i < cipher.size(); i++) {
//     if (c == cipher.at(i)) {
//       cipherIndex = i;
//     }
//   }
//   return cipherIndex;
// }

string applySubstCipher(const vector<char>& cipher, const string& s) {
  string cipherText = "";
  for (int i = 0; i < s.size(); i++) {
    if (!isalpha(s.at(i))) {
      cipherText += s.at(i);
    } else {
      int cipherIndex = ALPHABET.find(toupper(s.at(i)));
      cipherText += cipher.at(cipherIndex);
    }
  }

  return cipherText;
}

void applyRandSubstCipherCommand() {
  string plainText;
  cout << "Enter the text to substitution-cipher encrypt: " << endl;
  getline(cin, plainText);

  vector<char> subCipher = genRandomSubstCipher();

  cout << applySubstCipher(subCipher, plainText) << endl;
}

#pragma endregion SubstEnc

#pragma region SubstDec

vector<string> convertToQuadrgrams(const string& s) {
  vector<string> textQuadgrams;
  if (s.size() < 4) {
    return {};
  }

  for (int i = 0; i < s.size() - 3; i++) {
    textQuadgrams.push_back(s.substr(i, 4));
  }
  return textQuadgrams;
}

double scoreString(const QuadgramScorer& scorer, const string& s) {
  vector<string> quadgrams = convertToQuadrgrams(s);
  double englishnessScore = 0;
  for (int i = 0; i < quadgrams.size(); i++) {
    englishnessScore += scorer.getScore(quadgrams.at(i));
  }

  return englishnessScore;
}

void computeEnglishnessCommand(const QuadgramScorer& scorer) {
  string computeEnglish;

  cout << "Enter a string to score: " << endl;
  getline(cin, computeEnglish);

  string tempstr = "";
  for (int i = 0; i < computeEnglish.size(); i++) {
    if (isalpha(computeEnglish.at(i))) {
      tempstr += toupper(computeEnglish.at(i));
    }
  }
  computeEnglish = tempstr;

  double englishScore = scoreString(scorer, computeEnglish);

  cout << "Englishness: " << englishScore << endl;
}

vector<char> swapRandomLetters(vector<char>& cipher, int& index1, int& index2) {
  index1 = Random::randInt(25);
  index2 = Random::randInt(25);

  while (index2 == index1) {
    index2 = Random::randInt(25);
  }

  // char tempKey = cipher.at(index1);
  // cipher.at(index1) = cipher.at(index2);
  // cipher.at(index2) = tempKey;
  swap(cipher.at(index1), cipher.at(index2));
  return cipher;
}

vector<char> decryptSubstCipher(const QuadgramScorer& scorer,
                                const string& ciphertext) {
  vector<char> subCipher = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                            'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                            'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  // for (int i = 0; i < ALPHABET.size(); i++) {
  //   subCipher.push_back(ALPHABET.at(i));
  // }
  string decryptedText = applySubstCipher(subCipher, ciphertext);
  double max = scoreString(scorer, decryptedText);

  for (int i = 0; i < 20; i++) {
    vector<char> testKey = genRandomSubstCipher();

    string decryptedTextTest = applySubstCipher(testKey, ciphertext);
    double decryptionScore = scoreString(scorer, decryptedTextTest);
    // cout << "decrypted text " << decryptedTextTest << " " << "current score "
    //      << decryptionScore << " max score " << max << endl;

    int noImprovements = 0;
    while (noImprovements < 1500) {
      vector<char> newTestKey = testKey;
      int index1, index2;
      newTestKey = swapRandomLetters(newTestKey, index1, index2);

      string newDecryptedTextTest = applySubstCipher(newTestKey, ciphertext);
      double newDecryptionScore = scoreString(scorer, newDecryptedTextTest);

      if (newDecryptionScore > decryptionScore) {
        testKey = newTestKey;
        decryptionScore = newDecryptionScore;
        noImprovements = 0;
      } else {
        noImprovements++;
        swap(newTestKey.at(index1), newTestKey.at(index2));
      }
    }
    if (decryptionScore > max) {
      subCipher = testKey;
      max = decryptionScore;
    }
  }

  return subCipher;
}

void decryptSubstCipherCommand(const QuadgramScorer& scorer) {
  string cipherText;
  cout << "Enter text to substitution-cipher decrypt: " << endl;
  getline(cin, cipherText);

  // string tempstr = "";
  // for (int i = 0; i < cipherText.size(); i++) {
  //   if (isalpha(cipherText.at(i))) {
  //     tempstr += toupper(cipherText.at(i));
  //   } else {
  //     tempstr += cipherText.at(i);
  //   }
  // }
  // for (int i = 0; i < cipherText.size(); i++) {
  //   if (isalpha(cipherText.at(i))) {
  //     tempstr += toupper(cipherText.at(i));
  //   } else {
  //     break;
  //   }
  // }
  // cipherText = tempstr;
  string cleaned = clean(cipherText);

  vector<char> key = decryptSubstCipher(scorer, cleaned);
  string plainText = applySubstCipher(key, cipherText);

  cout << plainText << endl;
}

#pragma endregion SubstDec
