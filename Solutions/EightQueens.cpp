#include <iostream>
#include <vector>
using namespace std;

const char QUEEN = '*';
const int EXPECTED_QUEEN_COUNT = 8;
const int SIZE = 8;

bool isValidQueen(vector<vector<char>>& board, int queenRow, int queenCol) {
    // Search down
    for (int r = queenRow + 1; r < SIZE; r++)
        if (board[r][queenCol] == QUEEN)
            return false;

    // Search right
    for (int c = queenCol + 1; c < SIZE; c++)
        if (board[queenRow][c] == QUEEN)
            return false;

    // Search lower-left diagonal
    for (int r = queenRow + 1, c = queenCol - 1; r < SIZE && c >= 0; r++, c--)
        if (board[r][c] == QUEEN)
            return false;

    // Search lower-right diagonal    
    for (int r = queenRow + 1, c = queenCol + 1; r < SIZE && c < SIZE; r++, c++)
        if (board[r][c] == QUEEN)
            return false;

    return true;
}

int main() {
    vector<vector<char>> board(SIZE, vector<char>(SIZE));

    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            cin >> board[r][c];

    // Check that there are 8 queens
    int numQueens = 0;
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            if (board[r][c] == QUEEN)
                numQueens++;

    if (numQueens != EXPECTED_QUEEN_COUNT) {
        cout << "invalid" << endl;
        return 0;
    }
    
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == QUEEN && !isValidQueen(board, r, c)) {
                cout << "invalid" << endl;
                return 0;
            }
        }
    }

    cout << "valid" << endl;
    return 0;
}