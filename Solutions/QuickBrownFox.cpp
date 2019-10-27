#include <iostream>
#include <sstream>    // istringstream
#include <cctype>     // isalpha(), tolower()
#include <set>
#include <string>
using namespace std;

// Returns a set of unique characters in a string (as all lower-case)
set<char> getUniqueCharacters(string phrase) {
    set<char> uniqueLetters;
    istringstream stream(phrase);
    string word;

    while (stream >> word)
        for (char c : word)
            if (isalpha(c))
                uniqueLetters.insert(tolower(c));

    return uniqueLetters;
}

int main() {
    int testCases;
    cin >> testCases;

    // Ignore '/n' escape character so that getline() works properly later
    cin.ignore();

    // For each test case:
    // - Parse the phrase and get all unique characters (as lowercase)
    // - Build up a string of all lowercase letters that were not seen in the phrase
    // - Output based on if there were missing letters or not
    while (testCases--) {
        string phrase;
        getline(cin, phrase);

        set<char> uniqueLetters = getUniqueCharacters(phrase);

        string allLowerCaseLetters = "abcdefghijklmnopqrstuvwxyz";
        string missingLetters = "";

        for (char letter : allLowerCaseLetters)
            if (uniqueLetters.find(letter) == uniqueLetters.end())
                missingLetters += letter;

        if (missingLetters.empty())
            cout << "pangram" << endl;
        else
            cout << "missing " << missingLetters << endl;
    }

    return 0;
}
