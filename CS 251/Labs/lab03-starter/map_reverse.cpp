#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

// TODO student: update signature
/**
 * Returns a new map that is the "reversal" of the given map `m`.
 * For example, the map `{{"key", "value"}}` would be reversed to the map
 * `{{"value", "key"}}`.
 */
map < string, vector<string> reverseMap(vector<string> &x, vector<string> &y) {
  map < string, vector<string> reversedMap;
  for (int i = 0; i < x.size(); i++) {
    if (reversedMap.count(x.at(i))) {
      reversedMap.at(x.at(i)).push_back(y.at(i));
    }
    reversedMap.emplace(x.at(i), y.at(i));
  }

  return reversedMap;
}

void getKeysAndValue(vector<string> &x, vector<string> &y,
                     map<string, string> m) {
  for (auto &[key, value] : m) {
    x.push_back(key);
    y.push_back(value);
  }
}

int main() {
  // Because you're changing the signature, we don't have tests for this
  // function. Instead, update this example to demonstrate that your function
  // works as intended!
  map<string, string> example = {
      {"key", "value"},
      {"key 2", "value 2"},
      {"other key", "value"},
  };

  vector<string> keys;
  vector<string> values;
  getKeysAndValue(keys, values, example);

  example.clear();
  example = reverseMap(values, keys);

  for (auto &[key, value] : example) {
    cout << key << " : " << value << endl;
  }
}
