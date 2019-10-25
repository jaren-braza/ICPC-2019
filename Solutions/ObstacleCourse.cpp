#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct Coordinate {
    int row;
    int col;

    Coordinate() : row(0), col(0) {}
    Coordinate(int r, int c) : row(r), col(c) {}
    Coordinate(const Coordinate& coordinate) {
        row = coordinate.row;
        col = coordinate.col;
    }
};

class Solver {
    const int INF = INT32_MAX;
    vector<vector<int>> graph;
    vector<vector<bool>> visited;
    vector<vector<int>> minDistance;
    multimap<int, Coordinate> priorityQueue;
    int size;

public:
    Solver(int N);
    int dijkstra();

private:
    vector<Coordinate> getNeighbors(Coordinate cell);
};

int main() {
    int currentProblemNumber = 1;
    int N;

    while ((cin >> N) && (N != 0)) {
        Solver solver(N);
        cout << "Problem " << currentProblemNumber << ": " << solver.dijkstra() << endl;
        currentProblemNumber++;
    }

    return 0;
}

Solver::Solver(int sideLength) {
    // Set board size
    size = sideLength;

    // Set each cell as unvisited
    visited = vector<vector<bool>>(size, vector<bool>(size, false));

    // Set each cell as having an infinite minimum path distance
    minDistance = vector<vector<int>>(size, vector<int>(size, INF));

    // Parse the graph
    graph = vector<vector<int>>(size, vector<int>(size));
    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            cin >> graph[r][c];
}

// Returns the minimal path distance from the top-left corner to the bottom-right corner
int Solver::dijkstra() {
    // Start from the top left corner
    minDistance[0][0] = graph[0][0];
    priorityQueue.insert({ minDistance[0][0], Coordinate(0, 0) });

    while (!priorityQueue.empty()) {
        // Get the cell with the minimal path distance from the priority queue
        Coordinate cell = (priorityQueue.begin())->second;

        // Pop this cell
        priorityQueue.erase(priorityQueue.begin());

        if (visited[cell.row][cell.col])
            continue;

        visited[cell.row][cell.col] = true;

        // Visit each neighbor and attempt to update the minimal path distance
        for (Coordinate neighbor : getNeighbors(cell)) {
            if (visited[neighbor.row][neighbor.col])
                continue;

            int currentDistance = minDistance[cell.row][cell.col] + graph[neighbor.row][neighbor.col];

            if (currentDistance < minDistance[neighbor.row][neighbor.col])
                minDistance[neighbor.row][neighbor.col] = currentDistance;

            priorityQueue.insert({ minDistance[neighbor.row][neighbor.col], neighbor });
        }
    }

    // Return the minimal path distance to the bottom-right corner
    return minDistance[size - 1][size - 1];
}

vector<Coordinate> Solver::getNeighbors(Coordinate cell) {
    vector<Coordinate> neighbors;

    // Set values of coordinates to visit
    const int DIRECTIONS = 4;
    int dr[] = { -1,  0,  1,  0 };
    int dc[] = { 0, -1,  0,  1 };

    // Add the coordinate of each neighbor, if it is within the bounds of the board
    for (int i = 0; i < DIRECTIONS; i++) {
        int r = cell.row + dr[i];
        int c = cell.col + dc[i];

        if (r < 0 || r == size || c < 0 || c == size)
            continue;

        neighbors.push_back(Coordinate(r, c));
    }

    return neighbors;
}