#ifndef TST_NEWGTC_H
#define TST_NEWGTC_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "pokerhand.h"
#include "card.h"
#include "deck.h"

#include <iostream>
#include <stdexcept>
//#include <iomanip>
//#include <cstdlib>
#include <vector>

using namespace testing;

TEST(newgt, newgtc)
{
	EXPECT_EQ(1, 1);
	ASSERT_THAT(0, Eq(0));
}

TEST(cardTest, createCard)
{
	char face = '2';
	Card testCard = Card('H', face);
	EXPECT_EQ(0,testCard.getSuit());
	EXPECT_EQ(0,testCard.getFace());
}

TEST(cardTest, failCreateCard){
	EXPECT_THROW(Card('B','2'), std::runtime_error);
	EXPECT_THROW(Card('H','1'), std::runtime_error);
}

TEST(deckTest, useDeck){
	Deck d = Deck();
	for(int i = 0; i < 52; i++){
		Card c = d.dealCard();
		std::cout << c.getSuit() << " " << c.getFace() << std::endl;
	}
	d.shuffle();
	for(int i = 0; i < 52; i++){
		Card c = d.dealCard();
		std::cout << c.getSuit() << " " << c.getFace() << std::endl;
	}
}


#endif // TST_NEWGTC_H
