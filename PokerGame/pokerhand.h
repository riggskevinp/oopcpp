#ifndef POKERHAND_H
#define POKERHAND_H

#include "card.h"
#include <vector>
#include <stdlib.h>

class PokerHand
{
public:
	PokerHand() = default;
	PokerHand(std::vector<Card>);
	void addCard(Card card);
	double getValue();

private:
	double calculateValue();
	std::vector<Card> cards;
	std::vector<int> faceCounts = std::vector<int>(13,0);
	std::vector<int> suitCounts = std::vector<int>(4,0);

};

#endif // POKERHAND_H
