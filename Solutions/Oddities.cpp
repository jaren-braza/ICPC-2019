#include <iostream>
using namespace std;

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        int numberToCheck;
        cin >> numberToCheck;

        if (numberToCheck % 2 == 0)
            cout << numberToCheck << " is even" << endl;
        else
            cout << numberToCheck << " is odd" << endl;
    }

    return 0;
}