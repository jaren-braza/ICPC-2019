#include <iostream>
#include <string>
using namespace std;

// Returns the value of this digit, from 0 to 35.
int getValue(char digit) {
    if (digit >= '0' && digit <= '9')
        return digit - '0';
    
    return tolower(digit) - 'a' + 10;
}

// Returns if each digit of the number is within the base.
bool isValidBase(string& num, long long base) {
    for (char digit : num)
        if (getValue(digit) >= base)
            return false;
        
    return true;
}

// Returns the number (as a given base) converted to base ten.
long computeToBaseTen(string& num, long long base) {
    long long result = 0;

    for (char digit : num)
        result = result * base + getValue(digit);

    return result;
}

// Returns if two numbers are equivalent in some pair of bases.
bool conversionExists(string& firstNum, string& secondNum) {
    const long long MIN_BASE = 2;
    const long long MAX_BASE = 36;

    for (long long firstBase = MIN_BASE; firstBase <= MAX_BASE; firstBase++) {
        for (long long secondBase = MIN_BASE; secondBase <= MAX_BASE; secondBase++) {
            if (!isValidBase(firstNum, firstBase) || !isValidBase(secondNum, secondBase))
                continue;

            if (computeToBaseTen(firstNum, firstBase) == computeToBaseTen(secondNum, secondBase))
                return true;
        }
    }
    
    return false;
}

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        string firstNum;
        string secondNum;
        cin >> firstNum >> secondNum;

        if (conversionExists(firstNum, secondNum))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }

    return 0;
}
