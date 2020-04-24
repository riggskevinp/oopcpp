#ifndef POKERGAME_H
#define POKERGAME_H

#include <vector>
#include <QObject>

#include "player.h"
#include "deck.h"

// PokerGame and Deck could be implemented as singletons


// Class for holding elements of a poker game
class PokerGame: public QObject
{
	Q_OBJECT
public:
	PokerGame(int numberOfPlayers);
	~PokerGame();
	void deal();
	void newHand();
	void showHands();
	int pot = 0;
	std::vector<Player*> players;
	void winner();
	Deck deck = Deck();

signals:
	void potChanged(int pot);

private:


};

#endif // POKERGAME_H
