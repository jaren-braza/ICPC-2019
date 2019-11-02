#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

int main() {
    map<char, double> probability;
    string line;

    while (getline(cin, line)) {
        if (line.empty())
            break;
        
        istringstream stream(line);
        char ch;
        double likeliness;
        stream >> ch >> likeliness;

        probability[ch] = likeliness;
    }

    while (getline(cin, line)) {
        double correctnessChance = 1;

        for (char ch : line)
            if (probability.find(ch) != probability.end())
                correctnessChance *= probability[ch];
        
        correctnessChance = (double)((int)(correctnessChance * 1000 + 0.5)) / 1000;
        cout << fixed << setprecision(3);
        cout << correctnessChance << endl;
    }

    return 0;
}
