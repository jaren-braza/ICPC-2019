#include <algorithm>    // reverse
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>      // istringstream
#include <string>
#include <vector>
using namespace std;

// Perform a standard string split on the string read-in from standard input
vector<string> getSplitParsedString();

int main() {
    int mapPieces;
    cin >> mapPieces;

    // Skip over any hanging escape characters, like '\n'
    cin.ignore();

    // Track the unique neighbors for each station
    map<string, set<string>> mapInfo;

    // Parse each map piece
    for (int i = 0; i < mapPieces; i++) {
        vector<string> stationNeighbors = getSplitParsedString();
        string describedStation = stationNeighbors[0];

        // Store neighbors in the map info
        // Note that relations are bi-directional
        for (int j = 1; j < stationNeighbors.size(); j++) {
            mapInfo[describedStation].insert(stationNeighbors[j]);
            mapInfo[stationNeighbors[j]].insert(describedStation);
        }
    }

    // Parse the starting station and goal station
    string start;
    string goal;
    cin >> start >> goal;

    // Track the parent station as { parent : source }
    map<string, string> parent;

    // Perform a full graph search
    queue<string> stationsToSearch;
    stationsToSearch.push(start);

    while (!stationsToSearch.empty()) {
        string current = stationsToSearch.front();
        stationsToSearch.pop();

        // Search unvisited neighboring stations
        // A station is marked as visited if it has a parent
        for (string neighbor : mapInfo[current]) {
            if (parent.find(neighbor) == parent.end()) {
                parent[neighbor] = current;
                stationsToSearch.push(neighbor);
            }
        }
    }

    // Print the path from the start to the goal station, if it exists
    if (parent.find(goal) != parent.end()) {
        vector<string> path;
        string current = goal;

        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }

        path.push_back(start);
        reverse(path.begin(), path.end());

        for (string station : path)
            cout << station << " ";
        cout << endl;
    }
    else
        cout << "no route found" << endl;

    return 0;
}

vector<string> getSplitParsedString() {
    vector<string> splitString;
    string str;
    string substring;

    getline(cin, str);
    istringstream stream(str);

    while (stream >> substring)
        splitString.push_back(substring);

    return splitString;
}