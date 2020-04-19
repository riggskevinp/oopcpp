#ifndef DECK_H
#define DECK_H

#include <utility>
#include <vector>

#include "card.h"

class Deck {
public:
	Card dealCard();
	void shuffle();

private:
	int currentIndex = 0;
	std::vector<Card> deckOfCards = {
		Card('H', '2'),
		Card('H', '3'),
		Card('H', '4'),
		Card('H', '5'),
		Card('H', '6'),
		Card('H', '7'),
		Card('H', '8'),
		Card('H', '9'),
		Card('H', 'T'),
		Card('H', 'J'),
		Card('H', 'Q'),
		Card('H', 'K'),
		Card('H', 'A'),
		Card('D', '2'),
		Card('D', '3'),
		Card('D', '4'),
		Card('D', '5'),
		Card('D', '6'),
		Card('D', '7'),
		Card('D', '8'),
		Card('D', '9'),
		Card('D', 'T'),
		Card('D', 'J'),
		Card('D', 'Q'),
		Card('D', 'K'),
		Card('D', 'A'),
		Card('C', '2'),
		Card('C', '3'),
		Card('C', '4'),
		Card('C', '5'),
		Card('C', '6'),
		Card('C', '7'),
		Card('C', '8'),
		Card('C', '9'),
		Card('C', 'T'),
		Card('C', 'J'),
		Card('C', 'Q'),
		Card('C', 'K'),
		Card('C', 'A'),
		Card('S', '2'),
		Card('S', '3'),
		Card('S', '4'),
		Card('S', '5'),
		Card('S', '6'),
		Card('S', '7'),
		Card('S', '8'),
		Card('S', '9'),
		Card('S', 'T'),
		Card('S', 'J'),
		Card('S', 'Q'),
		Card('S', 'K'),
		Card('S', 'A'),
	};
};

#endif // DECK_H
