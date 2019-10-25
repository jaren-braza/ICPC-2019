#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
	int numCards;
	cin >> numCards;

	vector<int> deck(numCards);

	for (int i = 0; i < numCards; i++)
		cin >> deck[i];

	stack<int> recentCards;
	int remainingCards = numCards;

	for (int i = 0; i < numCards; i++) {
		// If it exists, check the most recently unused card. Use it if it matches parity.
		if (!recentCards.empty() && recentCards.top() % 2 == deck[i] % 2) {
			recentCards.pop();
			remainingCards -= 2;
		}
		// If it exists, check the next card in the deck. Use it if it matches parity.
		else if (i != numCards - 1 && deck[i] % 2 == deck[i + 1] % 2) {
			i++;
			remainingCards -= 2;
		}
		// Otherwise, this card is not used. Store it for later use.
		else
			recentCards.push(deck[i]);
	}

	cout << remainingCards << endl;
	return 0;
}