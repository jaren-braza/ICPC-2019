#include <iostream>
#include <set>
#include <vector>
using namespace std;

bool isLatinSquare(vector<vector<int>>& matrix) {
    int N = matrix.size();

    // Check if each row has unique elements.
    for (int r = 0; r < N; r++) {
        set<int> seenElements;

        for (int c = 0; c < N; c++) {
            if (seenElements.find(matrix[r][c]) != seenElements.end())
                return false;
            
            seenElements.insert(matrix[r][c]);
        }
    }

    // Check if each column has unique elements.
    for (int c = 0; c < N; c++) {
        set<int> seenElements;

        for (int r = 0; r < N; r++) {
            if (seenElements.find(matrix[r][c]) != seenElements.end())
                return false;
            
            seenElements.insert(matrix[r][c]);
        }
    }

    // Each row and column have unique elements - this is a Latin Square.
    return true;
}

bool isReduced(vector<vector<int>>& matrix) {
    int N = matrix.size();

    // Check that the first column is sorted
    for (int r = 1; r < N; r++)
        if (matrix[r - 1][0] >= matrix[r][0])
            return false;

    // Check that the first row is sorted
    for (int c = 1; c < N; c++)
        if (matrix[0][c - 1] >= matrix[0][c])
            return false;

    // Both the first row and first column are sorted - is Reduced.
    return true;
}

int main() {
    int N;

    while (cin >> N) {
        vector<vector<int>> matrix(N, vector<int>(N));

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                char ch;
                cin >> ch;

                if (isdigit(ch))
                    matrix[r][c] = ch - '0';
                else
                    matrix[r][c] = ch - 'A' + 10;
            }
        }

        if (isLatinSquare(matrix)) {
            if (isReduced(matrix))
                cout << "Reduced" << endl;
            else
                cout << "Not Reduced" << endl;
        }
        else
            cout << "No" << endl;
    }

    return 0;
}