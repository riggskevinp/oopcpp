#include "pokergame.h"

//#include <iostream>

PokerGame::PokerGame(int numberOfPlayers)
{
	for(int i = 0; i < numberOfPlayers; i++){
		players.push_back(new Player());
	}
}

void PokerGame::deal()
{
	deck.shuffle();
	for(int i = 0; i < 5; i++){ // deal 5 cards
		for(Player *p : players){ // deal around the table
			p->acceptCard(deck.dealCard());
			pot += p->bet(2);
			emit potChanged(pot);
		}
	}
}

void PokerGame::newHand()
{
	for(auto p : players){
		p->newHand();
	}
}

void PokerGame::showHands()
{
	double highHandValue = 0;

	for(auto p : players){
		if(p->getHandValue() > highHandValue){
			highHandValue = p->getHandValue();
		}

	}

	int winners[5];
	int winnerCount = 0;
	for(int i = 0; i < players.size(); i++){
		if(players.at(i)->getHandValue() >= highHandValue){
			winners[i] = 1;
			winnerCount++;
		}
	}

	for(int i = 0; i < 5; i++){
		if(winners[i] == 1){
			players.at(i)->addChips(pot/winnerCount);
		}
	}

	pot = 0;
	emit potChanged(pot);
}
