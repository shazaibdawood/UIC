#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO student: FIXME!
void deduplicate(vector<string>& vec) {
  for (int i = 0; i < vec.size(); i++) {
    if(i < vec.size() - 1){
      if (vec.at(i) == vec.at(i + 1)) {
      vec.erase(vec.begin() + i);
      i--;
    }
    }
  }
}

int main() {
  vector<string> drinks = {
      "coffee",
      "coffee",
      "coffee",
      "hot chocolate",
      "tea",
      "tea",
  };

  deduplicate(drinks);

  // drinks should now contain {"coffee", "hot chocolate", "tea"}:
  for (const auto& d : drinks) {
    cout << d << endl;
  }
}
