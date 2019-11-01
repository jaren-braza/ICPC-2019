#include <iostream>
#include <map>
#include <queue>
#include <set>
using namespace std;

typedef pair<int, int> Point;

struct ComplementGraph {
    map<Point, set<Point>> neighbors;
    map<Point, bool> visited;
    map<Point, int> color;
    int allowedDistance;

    ComplementGraph(int allowedDistance, vector<Point>& customers);
    bool isTwoColorable();
    int computeManhattanDistance(Point& p1, Point& p2);
};

// Search for the smallest distance where:
// - There will only be two complete subgraphs.
// - A customer within a subgraph is at most the searched distance of other customers in that subgraph.
//
// The idea is pretty interesting:
// - What does it mean for the graph to have ONLY two complete subgraphs?
// --- If the complement was colored, each subgraph would have only one color associated with its nodes.
// - Why?
// --- Each subgraph of the graph would normally contain nodes a distance from each other.
// --- The complement of the graph should have the nodes of one subgraph to NOT connect to each other.
// --- That means, if we ONLY have TWO subgraphs, the complement should only be colored with TWO colors.
// ----- If there is more than two colors, the distance did not cover enough customers.
// ----- If there is at most two colors, nice! Search if it is possible with even smaller distances.
int getMinAllowedDistance(vector<Point>& customers);


int main() {
    int customerCount;
    cin >> customerCount;

    vector<Point> customers(customerCount);

    for (int i = 0; i < customerCount; i++)
        cin >> customers[i].first >> customers[i].second;

    cout << getMinAllowedDistance(customers) << endl;

    return 0;
}


int getMinAllowedDistance(vector<Point>& customers) {
    int low = 0;        // Minimum distance, where each company has only one customer
    int high = 2000;    // Maximum Manhattan distance for a 1000x1000 graph
    int distance;

    while (low < high) {
        distance = (low + high) / 2;
        ComplementGraph graph(distance, customers);
        
        if (graph.isTwoColorable())
            high = distance;
        else
            low = distance + 1;
    }

    return low;
}

// Construct graph information for two customers if they exceed the allowed distance.
// This creates the complement of the normal graph.
ComplementGraph::ComplementGraph(int allowedDistance, vector<Point>& customers) {
    const int UNCOLORED = -1;

    for (int i = 0; i < customers.size(); i++) {
        for (int j = i + 1; j < customers.size(); j++) {
            int distanceBetweenCustomers = computeManhattanDistance(customers[i], customers[j]);

            if (distanceBetweenCustomers > allowedDistance) {
                neighbors[customers[i]].insert(customers[j]);
                neighbors[customers[j]].insert(customers[i]);

                visited[customers[i]] = false;
                visited[customers[j]] = false;

                color[customers[i]] = UNCOLORED;
                color[customers[j]] = UNCOLORED;
            }
        }
    }
}

// Returns if the graph can be two-colored.
bool ComplementGraph::isTwoColorable() {
    Point currentCustomer = (neighbors.begin())->first;
    queue<Point> search;

    search.push(currentCustomer);
    color[currentCustomer] = 0;

    while (!search.empty()) {
        currentCustomer = search.front();
        search.pop();

        visited[currentCustomer] = true;

        int nextColor;

        if (color[currentCustomer] == 0)
            nextColor = 1;
        else
            nextColor = 0;

        for (Point neighbor : neighbors[currentCustomer]) {
            if (color[neighbor] == color[currentCustomer])
                return false;

            if (!visited[neighbor]) {
                color[neighbor] = nextColor;
                search.push(neighbor);
            }
        }
    }

    return true;
}

// Returns the Manhattan distance between two points.
int ComplementGraph::computeManhattanDistance(Point& p1, Point& p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
