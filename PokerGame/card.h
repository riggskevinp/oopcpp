#ifndef CARD_H
#define CARD_H

class Card
{
public:
	Card(char suit, char face);
	int getFace(){return this->face;}
	int getSuit(){return this->suit;}

private:
	int suit;
	int face;
};

#endif // CARD_H
