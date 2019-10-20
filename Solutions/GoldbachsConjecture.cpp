#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Generate all primes from 2 to the upper bound
set<int> generatePrimes(int upperBound) {
    set<int> primes;

    for (int i = 2; i <= upperBound; i++) {
        bool isPrime = true;

        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            primes.insert(i);
    }

    return primes;
}

int main() {
    const int LARGEST_EVEN_INPUT = 32000;
    int n;
    int x;

    set<int> primes = generatePrimes(LARGEST_EVEN_INPUT);

    cin >> n;

    while (n--) {
        vector<pair<int, int>> representations;
        cin >> x;

        // For each prime, check if its complement to add up to x exists
        for (int prime : primes) {
            // Exit early to avoid duplicates
            // For example, if x = 26, we do not want 3+23 AND 23+3
            if (prime > x / 2)
                break;

            if (primes.find(x - prime) != primes.end())
                representations.push_back(make_pair(prime, x - prime));
        }

        cout << x << " has " << representations.size() << " representation(s)" << endl;

        for (pair<int, int>& representation : representations)
            cout << representation.first << "+" << representation.second << endl;

        cout << endl;
    }

    return 0;
}