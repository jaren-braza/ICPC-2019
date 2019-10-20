#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        string message;
        cin >> message;

        // Find next largest square
        int length = 1;
        while (length * length < message.size())
            length++;
        
        // Create an (L x L) array and fill as much of it with the message
        // Fill the rest of the array with asterisks
        vector<vector<char>> secret(length, vector<char>(length));
        for (int i = 0; i < length * length; i++) {
            if (i < message.size())
                secret[i / length][i % length] = message[i];
            else
                secret[i / length][i % length] = '*';
        }

        // Print out the array as if it was rotated 90 degrees
        for (int col = 0; col < length; col++) {
            for (int row = length - 1; row >= 0; row--) {
                if (secret[row][col] != '*')
                    cout << secret[row][col];
            }
        }

        cout << endl;
    }

    return 0;
}