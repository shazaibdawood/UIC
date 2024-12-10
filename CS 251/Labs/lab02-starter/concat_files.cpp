#include "concat_files.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> readlines(const string& fname) {
  ifstream inFS;
  inFS.open(fname);

  if(!inFS.is_open())
  {
    cout << "Could not open reading file " << fname << endl;
    return {};
  }

  vector<string> newVec;
  
  while(!inFS.eof()){
    string fileData;
    getline(inFS, fileData);
    newVec.push_back(fileData);
  }
  newVec.erase(newVec.begin() + newVec.size());
  inFS.close();

  return newVec;
}

void concatFiles(const string& in_fname, const string& out_fname) {
  ifstream inFS;
  ofstream outFS;
  inFS.open(in_fname);
  outFS.open(out_fname);

  if(!outFS.is_open())
  {
    cout << "Could not open outfile " << out_fname << endl;
    return;
  }

  if(!inFS.is_open())
  {
    cout << "Could not open infile " << in_fname << endl;
    return;
  }
  
  while(!inFS.eof()){
    string fileData;
    getline(inFS, fileData);
    vector<string> newVec = readlines(fileData);

    for(int i = 0; i < newVec.size(); i++){
      outFS << newVec.at(i) << endl;
    }    
  }

  inFS.close();
}

int main() {
  string filename = "test_data/file2.txt";
  vector<string> newVec = readlines(filename);
  
  for(int i = 0; i < newVec.size(); i++){
    cout << newVec.at(i) << " | ";
  }
  return 0;
}
