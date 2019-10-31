#include <iostream>
#include <map>
#include <set>
using namespace std;

typedef pair<int, int> Point;

struct Graph {
    map<Point, set<Point>> edges;
    map<Point, bool> visited;
    int figures;
    int polygons;
    bool isPolygon;

    Graph();
    void parseEdges();
    void computeResults();
    void printResults();
    void visit(Point src);
};

int main() {
    Graph graph;

    graph.parseEdges();
    graph.computeResults();
    graph.printResults();

    return 0;
}

// Complex algorithm based on the eigendecomposition of the diagonalized version of the graph.
// Also, it sets the default state of the fields of the graph.
Graph::Graph() {
    figures = 0;
    polygons = 0;
    isPolygon = false;
}

// Parses the standard input for all points and edges.
// Funnily enough, parsing the input is the toughest part of the entire program.
//
// For each character in the input:
// - If it is a digit:
// --- Parse the rest of the number.
// --- Put this number into whichever is missing first in { x1, y1, x2, y2 }.
// --- If all coordinates have a valid value (which is when y2 gets a value):
// ----- Save the two points as an edge.
// ----- Save the two points as unvisited.
void Graph::parseEdges() {
    const int NOT_DEFINED = -1;
    int x1 = NOT_DEFINED;
    int x2 = NOT_DEFINED;
    int y1 = NOT_DEFINED;
    int y2 = NOT_DEFINED;
    char c;

    while (cin >> c) {
        if (!isdigit(c))
            continue;

        int value = c - '0';

        while (isdigit(cin.peek())) {
            cin >> c;
            value = value * 10 + (c - '0');
        }

        if (x1 == NOT_DEFINED)
            x1 = value;
        else if (y1 == NOT_DEFINED)
            y1 = value;
        else if (x2 == NOT_DEFINED)
            x2 = value;
        else {
            y2 = value;

            Point p1 = make_pair(x1, y1);
            Point p2 = make_pair(x2, y2);

            edges[p1].insert(p2);
            edges[p2].insert(p1);

            visited[p1] = false;
            visited[p2] = false;

            x1 = NOT_DEFINED;
            x2 = NOT_DEFINED;
            y1 = NOT_DEFINED;
            y2 = NOT_DEFINED;
        }
    }
}

// Returns the number of figures within the graph.
// Each valid DFS visit is an entire figure.
// Each figure where every vertex has exactly two neighbors is a polygon.
void Graph::computeResults() {
    for (auto keyValuePair : edges) {
        Point src = keyValuePair.first;

        if (!visited[src]) {
            isPolygon = true;
            figures++;

            visit(src);

            if (isPolygon)
                polygons++;
        }
    }
}

// Prints the number of geometric figures followed by the number of polygons.
void Graph::printResults() {
    cout << figures << " " << polygons << endl;
}

// Performs a DFS visit for a given point.
// Also tracks if the figure being searched is a polygon.
void Graph::visit(Point src) {
    visited[src] = true;
    set<Point> neighbors = edges[src];

    if (neighbors.size() != 2)
        isPolygon = false;

    for (Point neighbor : neighbors)
        if (!visited[neighbor])
            visit(neighbor);
}