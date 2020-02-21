#ifndef CARD_H
#define CARD_H

class Card
{
public:
	Card(char suit, char face);
	int getFace(){return this->face;}
	char getSuit(){return this->suit;}

private:
	char suit;
	int face;
};

#endif // CARD_H
