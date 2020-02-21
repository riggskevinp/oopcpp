#ifndef TST_NEWGTC_H
#define TST_NEWGTC_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "pokerhand.h"
#include "card.h"

#ifdef _WIN32
#define LIBCONFIG_STATIC
#include <../../libconfig/lib/libconfig.h++>
#endif

#include <iostream>
#include <stdexcept>
//#include <iomanip>
//#include <cstdlib>

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
	EXPECT_EQ('H',testCard.getSuit());
	EXPECT_EQ(0,testCard.getFace());
}

TEST(cardTest, failCreateCard){
	EXPECT_THROW(Card('B','2'), std::runtime_error);
	EXPECT_THROW(Card('H','1'), std::runtime_error);
}


TEST(handTest, readConfig){
	libconfig::Config cfg;
	try
	{
		cfg.readFile("hand.cfg");
	}
	catch(const libconfig::FileIOException &fioex)
	{
		std::cerr << "I/O error while reading file." << std::endl;
	}
	catch(const libconfig::ParseException &pex)
	{
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
				  << " - " << pex.getError() << std::endl;
	}

	try{
		const libconfig::Setting& root = cfg.getRoot();
		const libconfig::Setting &cards = root["hand"]["cards"];
		int count = cards.getLength();

		for(int i = 0; i < count; i++){
			// Only output the record if all of the expected fields are present.
			const libconfig::Setting &card = cards[i];
			std::string suit;
			std::string face;


			if(!(card.lookupValue("suit", suit)
				&& card.lookupValue("face", face)
				)){
				std::cerr << "Failed to lookup" << std::endl;
			} else{
				EXPECT_EQ('H', suit.at(0));
				EXPECT_NE('T', suit.at(0));
			}
		}

	}
	catch(const libconfig::SettingNotFoundException &nfex)
	{
		std::cerr << "SettingNotFound " << nfex.what() << nfex.getPath() << std::endl;
	}
}

#endif // TST_NEWGTC_H
