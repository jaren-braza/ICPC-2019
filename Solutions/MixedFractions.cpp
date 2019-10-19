#include <iostream>
using namespace std;

int main() {
    int numerator;
    int denominator;

    while (cin >> numerator >> denominator) {
        if (numerator == 0 && denominator == 0)
            break;

        int wholeNumber = numerator / denominator;
        numerator = numerator % denominator;

        cout << wholeNumber << " "
             << numerator << " / "
             << denominator << endl;
    }

    return 0;
}