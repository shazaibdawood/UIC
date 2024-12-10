#include "application.h"

#include <iostream>
#include <limits>
#include <map>
#include <queue>  // priority_queue
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "dist.h"
#include "graph.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class prioritize {
   public:
    bool operator()(const pair<long long, double>& p1,
                    const pair<long long, double>& p2) const {
        return p1.second > p2.second;
    }
};


double INF = numeric_limits<double>::max();
priority_queue<pair<long long, double>,
               vector<pair<long long, double>>,
               prioritize>
    worklist;


void buildGraph(istream& input, graph<long long, double>& graphData, 
                vector<BuildingInfo>& buildingList) {
  json osmInput;
  input >> osmInput;

  map<long long, Coordinates> waypointMap;

  for (const auto& waypoint : osmInput["waypoints"]) {
    long long waypointID = waypoint.value("id", -1LL);
    double latitude = waypoint.value("lat", 0.0);
    double longitude = waypoint.value("lon", 0.0);

    graphData.addVertex(waypointID);
    waypointMap[waypointID] = {latitude, longitude};
  }

  for (const auto& path : osmInput["footways"]) {
    for (size_t i = 0; i + 1 < path.size(); ++i) {
      long long from = path[i].get<long long>();
      long long to = path[i + 1].get<long long>();

      if (waypointMap.count(from) == 1 && waypointMap.count(to) == 1) {
        double dist = distBetween2Points(waypointMap[from], waypointMap[to]);

        graphData.addEdge(from, to, dist);
        graphData.addEdge(to, from, dist);
      }
    }
  }

  for (const auto& buildingEntry : osmInput["buildings"]) {
    BuildingInfo building;
    building.id = buildingEntry.value("id", -1LL);
    building.name = buildingEntry.value("name", "");
    building.abbr = buildingEntry.value("abbr", "");
    building.location.lat = buildingEntry.value("lat", 0.0);
    building.location.lon = buildingEntry.value("lon", 0.0);

    buildingList.push_back(building);
    graphData.addVertex(building.id);      
  }

  for (const auto& building : buildingList) {
    for (const auto& [waypointID, waypointCoords] : waypointMap) {
      double proximity = distBetween2Points(building.location, waypointCoords);
      if (proximity <= 0.036) {
        graphData.addEdge(building.id, waypointID, proximity);
        graphData.addEdge(waypointID, building.id, proximity);
      }
    }
  }
}


BuildingInfo getBuildingInfo(const vector<BuildingInfo>& buildings,
                             const string& query) {
  for (const BuildingInfo& building : buildings) {
    if (building.abbr == query) {
      return building;
    } else if (building.name.find(query) != string::npos) {
      return building;
    }
  }
  BuildingInfo fail;
  fail.id = -1;
  return fail;
}

BuildingInfo getClosestBuilding(const vector<BuildingInfo>& buildings,
                                Coordinates c) {
  double minDestDist = INF;
  BuildingInfo ret = buildings.at(0);
  for (const BuildingInfo& building : buildings) {
    double dist = distBetween2Points(building.location, c);
    if (dist < minDestDist) {
      minDestDist = dist;
      ret = building;
    }
  }
  return ret;
}


vector<long long> dijkstra(const graph<long long, double>& G, long long start, long long target, const set<long long>& ignoreNodes) {
  map<long long, double> shortestDistance;
  map<long long, long long> previousVertexes;
  vector<long long> shortestPath;
  priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> worklist;
  set<long long> visited;
  set<long long> updatedIgnoreNodes;

  shortestPath.push_back(start);
  if(start == target){
    return shortestPath;
  }

  for(long long vertex : ignoreNodes){
    if(vertex != start && vertex != target){
      updatedIgnoreNodes.insert(vertex);
    }
  }

  for (long long vertex : G.getVertices()) {
    shortestDistance[vertex] = INF;
  }
  shortestDistance.at(start) = 0;

  worklist.push({start, 0});

  while (!worklist.empty()) {
    long long current = worklist.top().first;
    worklist.pop();

    if (visited.count(current) == 0) {
      visited.insert(current);

      if(current == target){
        vector<long long> temp;
        long long end = target;

        shortestPath.clear();

        while(end != start){
          temp.push_back(end);
          end = previousVertexes.at(end);
        }
        temp.push_back(start);

        for(int i = temp.size() - 1; i >= 0; i--){
          shortestPath.push_back(temp.at(i));
        }

        return shortestPath;
      }

      for(long long neighbor : G.neighbors(current)){
        if(updatedIgnoreNodes.count(neighbor) == 0){
          double weight;
          G.getWeight(current, neighbor, weight);

          double distance = shortestDistance.at(current) + weight;

          if(distance < shortestDistance.at(neighbor)){
            shortestDistance.at(neighbor) = distance;
            previousVertexes[neighbor] = current;
            worklist.push({neighbor, distance});
          }
        }
      }      
    }
  }

  shortestPath.clear();
  return shortestPath;
}


double pathLength(const graph<long long, double>& G,
                  const vector<long long>& path) {
  double length = 0.0;
  double weight;
  for (size_t i = 0; i + 1 < path.size(); i++) {
    bool res = G.getWeight(path.at(i), path.at(i + 1), weight);
    if (!res) {
      return -1;
    }
    length += weight;
  }
  return length;
}

void outputPath(const vector<long long>& path) {
  for (size_t i = 0; i < path.size(); i++) {
    cout << path.at(i);
    if (i != path.size() - 1) {
      cout << "->";
    }
  }
  cout << endl;
}

void application(const vector<BuildingInfo>& buildings,
                 const graph<long long, double>& G) {
  string person1Building, person2Building;

  set<long long> buildingNodes;
  for (const auto& building : buildings) {
    buildingNodes.insert(building.id);
  }

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);

  while (person1Building != "#") {
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);

    // Look up buildings by query
    BuildingInfo p1 = getBuildingInfo(buildings, person1Building);
    BuildingInfo p2 = getBuildingInfo(buildings, person2Building);
    Coordinates P1Coords, P2Coords;
    string P1Name, P2Name;

    if (p1.id == -1) {
      cout << "Person 1's building not found" << endl;
    } else if (p2.id == -1) {
      cout << "Person 2's building not found" << endl;
    } else {
      cout << endl;
      cout << "Person 1's point:" << endl;
      cout << " " << p1.name << endl;
      cout << " " << p1.id << endl;
      cout << " (" << p1.location.lat << ", " << p1.location.lon << ")" << endl;
      cout << "Person 2's point:" << endl;
      cout << " " << p2.name << endl;
      cout << " " << p2.id << endl;
      cout << " (" << p2.location.lon << ", " << p2.location.lon << ")" << endl;

      Coordinates centerCoords = centerBetween2Points(p1.location, p2.location);
      BuildingInfo dest = getClosestBuilding(buildings, centerCoords);

      cout << "Destination Building:" << endl;
      cout << " " << dest.name << endl;
      cout << " " << dest.id << endl;
      cout << " (" << dest.location.lat << ", " << dest.location.lon << ")"
           << endl;

      vector<long long> P1Path = dijkstra(G, p1.id, dest.id, buildingNodes);
      vector<long long> P2Path = dijkstra(G, p2.id, dest.id, buildingNodes);

      // This should NEVER happen with how the graph is built
      if (P1Path.empty() || P2Path.empty()) {
        cout << endl;
        cout << "At least one person was unable to reach the destination "
                "building. Is an edge missing?"
             << endl;
        cout << endl;
      } else {
        cout << endl;
        cout << "Person 1's distance to dest: " << pathLength(G, P1Path);
        cout << " miles" << endl;
        cout << "Path: ";
        outputPath(P1Path);
        cout << endl;
        cout << "Person 2's distance to dest: " << pathLength(G, P2Path);
        cout << " miles" << endl;
        cout << "Path: ";
        outputPath(P2Path);
      }
    }

    //
    // another navigation?
    //
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);
  }
}
