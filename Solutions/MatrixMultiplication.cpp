#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// 1000*1000 2*2
// 


// M[n1, m1] * M[n2, m2] = M[n1, m2]
struct Matrix {
	int n;
	int m;
	Matrix() : n(0), m(0) {}
	Matrix(int _n, int _m) : n(_n), m(_m) {}
};

vector<Matrix> parseInput() {
	vector<Matrix> matrices;
	string line;
	getline(cin, line);

	int numStart;
	int n;
	int m;

	for (int i = 0; i < line.size(); i++) {
		// Start of first dimension.
		if (line[i] == '[') {
			numStart = i + 1;
		}

		// End of first dimension, so store the digits we came across so far.
		// Start of second dimension.
		else if (line[i] == ',') {
			string numStr = line.substr(numStart, i - numStart);
			n = stoi(numStr);
			numStart = i + 1;
		}

		// End of second dimension, so store the digits we came across so far.
		// Also, store this matrix, since we have both dimensions now.
		else if (line[i] == ']') {
			string numStr = line.substr(numStart, i - numStart);
			m = stoi(numStr);
			matrices.push_back(Matrix(n, m));
		}

		// Intentionally blank. We ignore all other characters.
		else;
	}

	return matrices;
}

int main() {
	while (true) {
		vector<Matrix> matrices = parseInput();

		// End-of-file reached.
		if (matrices.empty())
			break;

		int N = matrices.size();
		vector<vector<int>> memo(N, vector<int>(N));

		// Fill first diagonal with initial matrix multiplications
		for (int i = 0; i < N - 1; i++) {
			memo[i][i + 1] = matrices[i].n * matrices[i + 1].m;
		}

		for (int d = 2; d < N - 1; d++) {
			for (int i = 0; i < N - d; i++) {
				int best = min(memo[i][i + d - 1], memo[i + 1][i + d]);
				memo[i][i + d] = matrices[i].n * matrices[i + d].m + best;
			}
		}

		cout << min(memo[0][N - 2], memo[1][N - 1]) << endl;
	}

	return 0;
}