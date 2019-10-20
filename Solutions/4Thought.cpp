#include <iostream>
#include <vector>
using namespace std;

vector<string> computeEquations() {
    vector<string> operations = { "*", "+", "-", "/" };
    vector<string> equations;

    for (string op1 : operations)
        for (string op2 : operations)
            for (string op3 : operations)
                equations.push_back(op1 + op2 + op3);
                
    return equations;
}

// Copy all values except for the value at the index
void copyExceptForIndex(vector<int>& values, int indexToAvoid) {
    vector<int> valuesCopy(values.size() - 1);
    int idx = 0;

    for (int i = 0; i < values.size(); i++) {
        if (i == indexToAvoid + 1)
            continue;

        valuesCopy[idx] = values[i];
        idx++;
    }

    values = valuesCopy;
}

// Compute the equation and see if it matches the solution
bool isCorrectEquation(string equation, int solution) {
    vector<int> values = { 4, 4, 4, 4 };

    // Go through all operations in the equation
    // - If there is a multiplication/division operation
    // --- Compute the operation and adjust the "values"
    // - Else (only addition/subtraction operations left)
    // --- Compute the operation and adjust the "values"
    while (!equation.empty()) {
        bool operationDone = false;
        int indexOfOperation = 0;
        
        // Do multiplication / division first
        for (int i = 0; i < equation.size(); i++) {
            if (equation[i] == '*' || equation[i] == '/') {
                if (equation[i] == '*')
                    values[i] = values[i] * values[i + 1];
                else
                    values[i] = values[i] / values[i + 1];

                operationDone = true;
                indexOfOperation = i;
                equation.erase(equation.begin() + i);
                break;
            }
        }

        if (operationDone) {
            copyExceptForIndex(values, indexOfOperation);
            continue;
        }

        // Do addition / subtraction first
        for (int i = 0; i < equation.size(); i++) {
            if (equation[i] == '+')
                values[i] = values[i] + values[i + 1];
            else
                values[i] = values[i] - values[i + 1];

            operationDone = true;
            indexOfOperation = i;
            equation.erase(equation.begin() + i);
            break;
        }

        copyExceptForIndex(values, indexOfOperation);
    }

    return values[0] == solution;
}

int main() {
    int testCases;
    int solution;
    
    cin >> testCases;

    for (int testCase = 0; testCase < testCases; testCase++) {
        vector<string> equations = computeEquations();
        cin >> solution;

        bool hasCorrectEquation = false;

        for (string equation : equations) {
            if (isCorrectEquation(equation, solution)) {
                cout << "4 " << equation[0] << " "
                     << "4 " << equation[1] << " "
                     << "4 " << equation[2] << " "
                     << "4 = " << solution << endl;

                hasCorrectEquation = true;
                break;
            }
        }

        if (!hasCorrectEquation)
            cout << "no solution" << endl;
    }

    return 0;
}