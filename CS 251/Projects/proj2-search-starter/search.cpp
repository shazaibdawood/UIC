// Shazaib Dawood
// CS 251

#include "include/search.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// removes trailing and leading punctions
// returned string is lowercase
string cleanToken(const string& token) {
  int begining = 0;
  int ending = token.length() - 1;

  // find beginning of string where leading punctuation ends
  while (begining < token.length() && ispunct(token.at(begining))) {
    begining++;
  }

  // find ending of string where trailing punctuation starts
  while (ending >= begining && ispunct(token.at(ending))) {
    ending--;
  }

  // returns if whole string is punctuation
  if (ending < begining) {
    return "";
  }

  // build the new lowercase string
  string cleanedToken = "";
  bool hasLetter = false;
  for (int i = begining; i < ending + 1; i++) {
    if (isalpha(token.at(i))) {
      hasLetter = true;
    }
    cleanedToken += tolower(token.at(i));
  }
  if (!hasLetter) {
    return "";
  }
  // cout << cleanedToken << endl;
  return cleanedToken;
}

// cleans up all words in the sentence
// returns a set of cleaned words
set<string> gatherTokens(const string& text) {
  istringstream inSS(text);
  set<string> words;
  string rawWord;

  while (inSS >> rawWord) {
    string cleanedWord = cleanToken(rawWord);

    // checks for empty strings
    if (cleanedWord.length() > 0) {
      words.insert(cleanedWord);
    }
  }

  return words;
}

// sets each word to a key and its value is how many webpages the word is in
// returns the number of webpages
int buildIndex(const string& filename, map<string, set<string>>& index) {
  ifstream inFS;
  inFS.open(filename);
  if (!inFS.is_open()) {
    // return if file not found
    // cout << filename << " not open" << endl;
    return 0;
  }

  string webPage;
  string rawData;
  int webPageCounter = 0;
  set<string> words;
  while (!inFS.eof()) {
    getline(inFS, webPage);

    // check if webpage is empty
    if (webPage.length() == 0) {
      break;
    }
    // if (webPage.at(webPage.size() - 4) != '.') {
    //   cout << "Not a webpage" << endl;
    //   return 0;
    // }

    webPageCounter++;
    getline(inFS, rawData);

    words = gatherTokens(rawData);
    for (auto i : words) {
      // if key already exists then add webpage to set
      // or else add the key and the value to the map
      if (index.count(i)) {
        index.at(i).insert(webPage);
      } else {
        set<string> tempSet;
        tempSet.insert(webPage);
        index.emplace(i, tempSet);
      }
    }
  }
  inFS.close();
  // for (auto [key, value] : index) {
  //   cout << key << ": ";
  //   for (auto i : value) {
  //     cout << i << " ";
  //   }
  //   cout << endl;
  // }

  return webPageCounter;
}

// returns the set of webpages of the words of the sentence
// uses set operations
set<string> findQueryMatches(const map<string, set<string>>& index,
                             const string& sentence) {
  istringstream inSS(sentence);
  vector<string> searchTerms;
  string searchTerm;

  while (inSS >> searchTerm) {
    if (searchTerm.length() > 0) {
      searchTerms.push_back(searchTerm);
    }
  }

  set<string> pages;

  // checks if first word is in index
  searchTerm = cleanToken(searchTerms.at(0));
  if (index.count(searchTerm) == 1) {
    pages = index.at(searchTerm);
  }

  for (int i = 1; i < searchTerms.size(); i++) {
    searchTerm = searchTerms.at(i);
    char mode = searchTerm.at(0);
    searchTerm = cleanToken(searchTerm);

    // skip word if not in index
    if (!index.count(searchTerm)) {
      continue;
    }
    set<string> temp;

    if (mode == '+') {
      temp.clear();
      set_intersection(pages.begin(), pages.end(), index.at(searchTerm).begin(),
                       index.at(searchTerm).end(),
                       inserter(temp, temp.begin()));
      pages = temp;
    } else if (mode == '-') {
      temp.clear();
      set_difference(pages.begin(), pages.end(), index.at(searchTerm).begin(),
                     index.at(searchTerm).end(), inserter(temp, temp.begin()));
      pages = temp;
    } else {
      temp.clear();
      set_union(pages.begin(), pages.end(), index.at(searchTerm).begin(),
                index.at(searchTerm).end(), inserter(temp, temp.begin()));
      pages = temp;
    }
  }

  return pages;
}

// gets a file and a sentence to search
// prints out the webpages that each word is in based on the set operation
// specified
void searchEngine(const string& filename) {
  ifstream inFS;
  inFS.open(filename);
  if (!inFS.is_open()) {
    cout << "Invalid filename." << endl;
  }
  inFS.close();
  cout << "Stand by while building index..." << endl;

  map<string, set<string>> index;
  int numWebPages = buildIndex(filename, index);
  cout << "Indexed " << numWebPages << " pages containing " << index.size()
       << " unique terms" << endl;
  cout << endl;

  string sentence;
  cout << "Enter query sentence (press enter to quit): ";
  getline(cin, sentence);
  cout << endl;

  while (sentence != "") {
    set<string> URLs = findQueryMatches(index, sentence);
    cout << "Found " << URLs.size() << " matching pages" << endl;

    for (auto i : URLs) {
      cout << i << endl;
    }
    cout << endl;

    cout << "Enter query sentence (press enter to quit): ";
    getline(cin, sentence);
    cout << endl;
  }
  cout << "Thank you for searching!" << endl;
}
