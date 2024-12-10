#include <fstream>
#include <map>
#include <sstream>

#include "heap.h"

vector<TrainStation> topK(vector<TrainStation> allStations, int k) {
  // TODO BY STUDENT
  // This function will return the top k elements in the order that they will be
  // removed from the min-heap in the end (i.e. in order of ascending ridership)
  // Thus, the top station, by ridership, will be in the end of the list.
  MinHeap h;

  for(TrainStation& station: allStations){
    h.insert(station);
    if(h.size() > k){
      h.remove();
    }
  }

  vector<TrainStation> topK;
  while(h.size() > 0){
    topK.push_back(h.remove());
  }
  return topK;
}

int main() {
  ifstream file("cta_ridership_perStation.csv");
  map<int, TrainStation> stationMap;
  string line;
  getline(file, line);  // Read the header line.

  // Read in the data for all stations and accumulate the ridership.
  while (getline(file, line)) {
    istringstream iss(line);
    string token;
    getline(iss, token, ',');  // read id
    int id = stoi(token);

    getline(iss, token, ',');  // read name
    string name = token;

    getline(iss, line, ',');  // discard date
    getline(iss, line, ',');  // discard daytype

    getline(iss, token, ',');  // read number of rides
    int rides = stoi(token);

    if (stationMap.count(id) == 0) {
      TrainStation ts;
      ts.id = id;
      ts.name = name;
      ts.ridership = rides;
      stationMap[id] = ts;
    } else {
      stationMap[id].ridership = stationMap[id].ridership + rides;
    }
  }

  // Put all the train stations in a vector.
  vector<TrainStation> allStations;
  for (pair<int, TrainStation> p : stationMap) {
    allStations.push_back(p.second);
  }

  int k = 10;
  vector<TrainStation> topKStations = topK(allStations, k);

  cout << "Top " << k << " stations in terms of ridership: " << endl;
  for (int i = 1; i <= k; i++) {
    int j = k - i;
    string name = topKStations[j].name;
    int ridership = topKStations[j].ridership;
    cout << i << ". " << name << " - " << ridership << " rides" << endl;
  }
}
