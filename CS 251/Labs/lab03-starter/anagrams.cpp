#include "anagrams.h"

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<string> findAnagrams(const string& word, const vector<string>& dictionary) {
  set<string> result;
  map<char, int> wordCompare;
  map<char, int> dictionaryCompare;

  for (int i = 0; i < word.size(); i++) {
    if (wordCompare.count(word[i])) {
      wordCompare.at(word[i]) += 1;
    } else {
      wordCompare.emplace(word[i], 1);
    }
  }
  for (int i = 0; i < dictionary.size(); i++) {
    if (dictionary[i].size() == word.size()) {
      for (int j = 0; j < dictionary[i].size(); j++) {
        if (dictionaryCompare.count(dictionary[i][j])) {
          dictionaryCompare.at(dictionary[i][j]) += 1;
        } else {
          dictionaryCompare.emplace(dictionary[i][j], 1);
        }
      }
      if (wordCompare == dictionaryCompare) {
        result.insert(dictionary[i]);
      }
      dictionaryCompare.clear();
    }
  }

  return result;
}

int main() {
  // TODO student: Add manual testing code, if desired
  return 0;
}
