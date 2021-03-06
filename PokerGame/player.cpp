#include "player.h"

Player::Player()
{

}

void Player::acceptCard(Card c)
{
	if(cards.size() < 5){
		cards.push_back(c);
	}
	if(cards.size() == 5){
		hand = PokerHand(cards);
		handValid = true;
	}
}

void Player::newHand(){
	cards.clear();
	handValid = false;
}

void Player::addChips(int c)
{
	chipCount += c;
	emit chipsChanged(chipCount);
}

double Player::getHandValue()
{
	if(handValid){
		return hand.getValue();
	} else {
		return 0;
	}
}

int Player::bet(int chips)
{
	if(chipCount >= chips){
		chipCount -= chips;
		emit chipsChanged(chipCount);
	}
	return chips;
}
