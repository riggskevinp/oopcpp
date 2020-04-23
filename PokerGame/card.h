#ifndef CARD_H
#define CARD_H

class Card
{
public:
	Card(char suit, char face);
	int getFace() const {return this->face;}
	int getSuit() const {return this->suit;}

private:
	int suit;
	int face;
};

#endif // CARD_H
