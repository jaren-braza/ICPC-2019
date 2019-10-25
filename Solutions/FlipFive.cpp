#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Board;

class Solver {
	const int SIZE = 3;
	const char BLACK = '*';
	const char WHITE = '.';
	Board currentBoard;
	Board targetBoard;
	int minClicks;
	int currentClicks;
public:
	Solver();
	void computeClicksToTarget(int row, int col);
	int getClicksToTarget();
private:
	void parseBoard();
	bool isSolved();
	bool isInBounds(int row, int col);
	void clickCell(int row, int col);
	void flip(int row, int col);
};

int main() {
	int testCases;
	cin >> testCases;

	while (testCases--) {
		Solver solver;
		solver.computeClicksToTarget(0, 0);
		cout << solver.getClicksToTarget() << endl;
	}

	return 0;
}

// Reads in the target board, and makes the current board all white
Solver::Solver() {
	currentBoard = Board(SIZE, vector<char>(SIZE, WHITE));
	parseBoard();
	minClicks = SIZE * SIZE; // In the worst case, we have to click every cell
	currentClicks = 0;
}

// Returns a 2D array, representing the target board, from standard input 
void Solver::parseBoard() {
	targetBoard = Board(SIZE, vector<char>(SIZE));

	for (int row = 0; row < SIZE; row++)
		for (int col = 0; col < SIZE; col++)
			cin >> targetBoard[row][col];
}

// Stores the minimum number of clicks to get from the starting board to the target board
void Solver::computeClicksToTarget(int row, int col) {
	// If this path won't be better than a previous path, just stop
	if (currentClicks >= minClicks)
		return;

	// If all cells have been explored, check if it matches the target board and update the answer
	if (row == SIZE) {
		if (isSolved())
			minClicks = currentClicks;
	}
	else {
		int initialRow = row;
		int initialCol = col;

		// Get to the next cell
		if (col == SIZE - 1) {
			row++;
			col = 0;
		}
		else
			col++;

		// Try to get to the target without clicking this cell
		computeClicksToTarget(row, col);
		clickCell(initialRow, initialCol);
		currentClicks++;

		// Try to get to the target with clicking this cell
		computeClicksToTarget(row, col);
		clickCell(initialRow, initialCol);
		currentClicks--;
	}
}

// Returns the minimum number of clicks to the target board
int Solver::getClicksToTarget() {
	return minClicks;
}

// Returns if the values of the current board matches those of the board from the input
bool Solver::isSolved() {
	for (int row = 0; row < SIZE; row++)
		for (int col = 0; col < SIZE; col++)
			if (currentBoard[row][col] != targetBoard[row][col])
				return false;

	return true;
}

// Returns if the coordinates for the cell is within the board
bool Solver::isInBounds(int row, int col) {
	return (row >= 0) && (row < SIZE) &&
		(col >= 0) && (col < SIZE);
}

// Flips this cell and every neighboring cell
void Solver::clickCell(int row, int col) {
	if (!isInBounds(row, col))
		return;

	// Flip this cell
	flip(row, col);

	// Flip the upper neighbor
	if (row > 0)
		flip(row - 1, col);

	// Flip the lower neighbor
	if (row < SIZE - 1)
		flip(row + 1, col);

	// Flip the left neighbor
	if (col > 0)
		flip(row, col - 1);

	// Flip the right neighbor
	if (col < SIZE - 1)
		flip(row, col + 1);
}

// Toggles this cell between black and white
void Solver::flip(int row, int col) {
	if (currentBoard[row][col] == BLACK)
		currentBoard[row][col] = WHITE;
	else
		currentBoard[row][col] = BLACK;
}
