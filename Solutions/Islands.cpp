#include <iostream>
#include <vector>
using namespace std;

// Returns if the row and column are within the bounds of the board
bool inBounds(vector<vector<char>>& board, int row, int col) {
    return (row >= 0) && (row < board.size()) && (col >= 0) && (col < board[0].size());
}

// Depth-first search
// - If we come across land (where clouds are optimistically assumed to be land)...
// - ...then we "sink" it, turning it to water, and explore its neighbors
void sinkIsland(vector<vector<char>>& board, int row, int col) {
    if (!inBounds(board, row, col))
        return;

    if (board[row][col] == 'W')
        return;

    board[row][col] = 'W';

    sinkIsland(board, row - 1, col);
    sinkIsland(board, row + 1, col);
    sinkIsland(board, row, col - 1);
    sinkIsland(board, row, col + 1);
}

int main() {
    int rows;
    int cols;
    cin >> rows >> cols;

    // Parse the board
    vector<vector<char>> board(rows, vector<char>(cols));

    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            cin >> board[row][col];

    int numIslands = 0;

    // Sink all islands
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (board[row][col] == 'L') {
                sinkIsland(board, row, col);
                numIslands++;
            }
        }
    }

    cout << numIslands << endl;
}
