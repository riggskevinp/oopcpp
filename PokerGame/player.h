#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <QObject>

#include "card.h"
#include "pokerhand.h"

// Player class agnostic to computer vs human controller
class Player: public QObject
{
	Q_OBJECT
public:
	Player();
	// take card from game, if five cards update hand
	void acceptCard(Card c);
	// clear current hand to get ready for next
	void newHand();
	// helpers for chips
	void addChips(int c);
	int getChipCount(){return chipCount;}
	// return the absolute value of hand
	double getHandValue();
	// control functions for manipulating player during hand
	void fold(){handValid = false;}
	int bet(int chips);
	// support viewing hand
	const std::vector<Card>& showCards(){return cards;}

signals:
	void chipsChanged(int floor);

private:
	PokerHand hand = PokerHand();
	bool handValid = false;
	std::vector<Card> cards;
	int chipCount = 200;

};

#endif // PLAYER_H
