#include "pokerhand.h"
#include <stdexcept>
#include <algorithm>

PokerHand::PokerHand(std::vector<Card> cards)
{
	if(cards.size() > 5){
		throw(std::invalid_argument("Too many cards, need 5 or less"));
	}
	this->cards = cards;
}

void PokerHand::addCard(Card card)
{
	if(this->cards.size() > 5){
		throw(std::range_error("Already 5 cards, can't add more"));
	}
	this->cards.push_back(card);
}

double PokerHand::getValue()
{
	if(value > 0){
		return value;
	}
	if(this->cards.size() != 5){
		return 0;
	} else {
		std::sort(cards.begin(), cards.end(),
				[](Card &a, Card &b)-> bool
					{
						return a.getFace() > b.getFace();
					});

		for(Card card : cards){
			++suitCounts[card.getSuit()];
			faceCounts[card.getFace()]++;
		}
		value = calculateValue();
		return value;

	}
}

double PokerHand::calculateValue()
{
	double value = 0;
	double cardValue = 0;

	bool isFlush = false;
	for(auto suit: suitCounts){
		if(suit > 4){
			isFlush = true;
		}
	}

	bool isStraight = false;
	for(int i = 0; i <= 8; i++){
		if(faceCounts.at(i) > 0
				&& faceCounts.at(i+1) > 0
				&& faceCounts.at(i+2) > 0
				&& faceCounts.at(i+3) > 0
				&& faceCounts.at(i+4) > 0){
			isStraight = true;
		}
	}

	bool isStraightFlush = false;
	if(isFlush && isStraight){
		isStraightFlush = true;
		return 10 + cards.at(0).getFace()*1e-2;
	}

	int fourOfKind = -1;
	int singleCard = -1;

	for(int i = 0; i < faceCounts.size(); i++){
		if(faceCounts.at(i) == 4){
			fourOfKind = i;
		}
		if(faceCounts.at(i) == 1){
			singleCard = i;
		}
	}

	if(fourOfKind >= 0){
		return 9 + fourOfKind*1e-2 + singleCard*1e-4;
	}

	int threeOfKind = -1;
	for(int i = 0; i < faceCounts.size(); i++){
		if(faceCounts.at(i) == 3){
			threeOfKind = i;
		}
	}

	int pair1 = -1;
	int pair2 = -1;

	for(int i = 0; i < faceCounts.size(); i++){
		if(faceCounts.at(i) == 2){
			if(pair1 == -1){
				pair1 = i;
			} else {
				pair2 = i;
			}
		}
	}

	bool isFullHouse = false;
	if(threeOfKind >= 0 && pair1 >= 0){
		isFullHouse = true;
		return 8 + threeOfKind*1e-2 + pair1*1e-4;
	}

	if(isFlush){
		return 7 + cards.at(0).getFace()*1e-2
				+ cards.at(1).getFace()*1e-4
				+ cards.at(2).getFace()*1e-6
				+ cards.at(3).getFace()*1e-8
				+ cards.at(4).getFace()*1e-10;
	}

	if(isStraight){
		return 6 + cards.at(0).getFace()*1e-2;
	}

	bool isThreeOfKind = false;
	if(threeOfKind >= 0){
		isThreeOfKind = true;
		std::vector<int> leftOver;
		for(int i = 0; i < faceCounts.size(); i++){
			if(faceCounts.at(i) < 3 && faceCounts.at(i) > 0){
				leftOver.push_back(i);
			}
		}
		return 5 + threeOfKind*1e-2 + leftOver.at(0)*1e-4 + leftOver.at(1)*1e-6;
	}

	bool isTwoPair = false;
	if(pair1 >= 0 && pair2 >= 0){
		isTwoPair = true;
		int leftOver = 0;
		for(int i = 0; i < faceCounts.size(); i++){
			if(faceCounts.at(i) < 2 && faceCounts.at(i) > 0){
				leftOver = i;
			}
		}
		return 4 + pair2*1e-2 + pair1*1e-4 + leftOver*1e-6;
	}

	bool isOnePair = false;
	if(pair1 >= 0){
		isOnePair = true;
		std::vector<int> leftOver;
		for(int i = 0; i < faceCounts.size(); i++){
			if(faceCounts.at(i) < 2 && faceCounts.at(i) > 0){
				leftOver.push_back(i);
			}
		}
		return 3 + pair1*1e-2 + leftOver.at(2)*1e-4 + leftOver.at(1)*1e-6 + leftOver.at(0)*1e-8;
	}

	bool isHighCard = true;
	return 2 + cards.at(0).getFace()*1e-2
			+ cards.at(1).getFace()*1e-4
			+ cards.at(2).getFace()*1e-6
			+ cards.at(3).getFace()*1e-8
			+ cards.at(4).getFace()*1e-10;
}
