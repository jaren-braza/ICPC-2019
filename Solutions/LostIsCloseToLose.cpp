#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Returns the alphabetically-filtered and all-lowercase version of the string.
string getCore(string word);

// Returns an array of all collected "cores" over the entire input.
vector<string> parseCores();

// Returns if the first string can be transformed into the second string.
// The three possible transformations are deletion, replacement, and transposition.
// Note that deletion always accounts for insertion.
bool canTransform(string& s1, string& s2);

// Returns if we can delete a single character from the larger string to equal the smaller string.
bool canDelete(string& s1, string& s2);

// Returns if we can replace a single character from the first string to equal the second string.
bool canReplace(string& s1, string& s2);

// Returns if we can swap two adjacent characters from the first string to equal the second string.
bool canTranspose(string& s1, string& s2);


// 1. Go through all pairs of cores and collect pairs that can transform to each other into a mapping.
// --- Match output by using an ordered mapping and set
// --- Avoid duplicates within map by using a set for the value
// --- Example: For input "aa aa \n ***", we avoid having {"aa" : ["aa", "aa"]}.
// 2. Go through each key-value entry in the mapping and output the results.
// --- If the mapping is empty, then simply output "***".
int main() {
    vector<string> cores = parseCores();
    map<string, set<string>> similarCoresMap;

    for (int i = 0; i < cores.size(); i++) {
        for (int j = i + 1; j < cores.size(); j++) {
            string firstCore = cores[i];
            string secondCore = cores[j];

            if (canTransform(firstCore, secondCore)) {
                similarCoresMap[firstCore].insert(secondCore);
                similarCoresMap[secondCore].insert(firstCore);
            }
        }
    }

    if (similarCoresMap.empty())
        cout << "***" << endl;
    else {
        for (auto keyValuePair : similarCoresMap) {
            string core = keyValuePair.first;
            set<string> similarCores = keyValuePair.second;

            cout << core << ": ";

            for (string similarCore : similarCores)
                cout << similarCore << " ";
            
            cout << endl;
        }
    }

    return 0;
}


string getCore(string word) {
    if (word == "***")
        return "***";

    string core = "";

    for (int i = 0; i < word.size(); i++)
        if (isalpha(word[i]))
            core += tolower(word[i]);

    return core;
}

vector<string> parseCores() {
    vector<string> cores;
    string line;

    while (getline(cin, line)) {
        istringstream stream(line);
        string word;

        while (stream >> word) {
            string core = getCore(word);
            
            // Use continue instead of break, incase of sneaky edge cases.
            // Example: "*** Get baited nerd you would not have parsed this using break".
            // Example: "All good until... *** you just got destroyed nerd".
            if (core == "***" || core.empty())
                continue;
            
            cores.push_back(core);
        }
    }

    return cores;
}

bool canTransform(string& s1, string& s2) {
    if (s1.size() == s2.size())
        return canReplace(s1, s2) || canTranspose(s1, s2);

    if (s1.size() > s2.size())
        return canDelete(s1, s2);
    
    return canDelete(s2, s1);
}

bool canDelete(string& s1, string& s2) {
    if (s1.size() != s2.size() + 1)
        return false;

    // Check if removing the i'th letter from the larger string makes it match the smaller string.
    for (int i = 0; i < s1.size(); i++) {
        string leftHalfWithoutI = s1.substr(0, i);
        string rightHalfWithoutI = s1.substr(i + 1, s1.size() - i - 1);

        if (leftHalfWithoutI + rightHalfWithoutI == s2)
            return true;
    }

    return false;
}

bool canReplace(string& s1, string& s2) {
    bool hasOneDifference = false;

    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) {
            if (hasOneDifference)
                return false;
            
            hasOneDifference = true;
        }
    }

    return hasOneDifference;
}

bool canTranspose(string& s1, string& s2) {
    for (int i = 0; i < s1.size() - 1; i++) {
        // If there is a difference, attempt the single chance to swap with the adjacent position.
        if (s1[i] != s2[i]) {
            string swapped = s1;
            swap(swapped[i], swapped[i + 1]);
            return swapped == s2;
        }
    }

    return false;
}
