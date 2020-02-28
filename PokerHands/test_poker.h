#ifndef TST_NEWGTC_H
#define TST_NEWGTC_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "pokerhand.h"
#include "card.h"
#include "readConfig.h"

#ifdef _WIN32
#define LIBCONFIG_STATIC
#include <../../libconfig/lib/libconfig.h++>
#endif

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

TEST(handTest, inputCard){
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
				Card testCard = Card(suit.at(0), face.at(0));
				EXPECT_EQ(0, testCard.getSuit());
				EXPECT_EQ(i, testCard.getFace());
			}
		}

	}
	catch(const libconfig::SettingNotFoundException &nfex)
	{
		std::cerr << "SettingNotFound " << nfex.what() << nfex.getPath() << std::endl;
	}
}


TEST(handTest, calcValue){

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

	std::vector<Card> cardVec;
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

				Card testCard = Card(suit.at(0), face.at(0));
				cardVec.push_back(testCard);
			}
		}

	}
	catch(const libconfig::SettingNotFoundException &nfex)
	{
		std::cerr << "SettingNotFound " << nfex.what() << nfex.getPath() << std::endl;
	}

	PokerHand hand = PokerHand(cardVec);
	EXPECT_EQ(10.04, hand.getValue());
}

TEST(handTest, useReadConfig){
	std::vector<Card> cards = readConfig("hand.cfg");
	PokerHand hand = PokerHand(cards);
	EXPECT_EQ(10.04, hand.getValue());
}

TEST(compareHands, straightFlush){
	std::vector<Card> cardsHigher1 = readConfig("10C9C8C7C6C.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("8H7H6H5H4H.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsHigher2 = readConfig("8H7H6H5H4H.cfg");
	PokerHand handHigher2 = PokerHand(cardsHigher2);
	std::vector<Card> cardsLower2 = readConfig("6S5S4S3S2S.cfg");
	PokerHand handLower2 = PokerHand(cardsLower2);
	EXPECT_GT(handHigher2.getValue(), handLower2.getValue());

	std::vector<Card> cardsEqual = readConfig("7C6C5C4C3C.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("7D6D5D4D3D.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}

TEST(compareHands, fourOfKind){
	std::vector<Card> cardsHigher1 = readConfig("KSKHKSKD3H.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("7H7D7S7CQH.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsHigher2 = readConfig("7H7D7S7CQH.cfg");
	PokerHand handHigher2 = PokerHand(cardsHigher2);
	std::vector<Card> cardsLower2 = readConfig("7H7D7S7CTH.cfg");
	PokerHand handLower2 = PokerHand(cardsLower2);
	EXPECT_GT(handHigher2.getValue(), handLower2.getValue());

	std::vector<Card> cardsEqual = readConfig("4C4S4D4H9C.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("4C4S4D4H9D.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}

TEST(compareHands, fullHouse){
	std::vector<Card> cardsHigher1 = readConfig("8C8D8H7D7C.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("4D4S4C9D9C.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsHigher2 = readConfig("4D4S4C9D9C.cfg");
	PokerHand handHigher2 = PokerHand(cardsHigher2);
	std::vector<Card> cardsLower2 = readConfig("4D4S4C5C5D.cfg");
	PokerHand handLower2 = PokerHand(cardsLower2);
	EXPECT_GT(handHigher2.getValue(), handLower2.getValue());

	std::vector<Card> cardsEqual = readConfig("KSKCKDJCJS.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("KSKHKDJCJH.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}

TEST(compareHands, flush){
	std::vector<Card> cardsHigher1 = readConfig("ADJDTD9D8D.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("KDJDTD9D8D.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsEqual = readConfig("ADJDTD9D8D.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("ACJCTC9C8C.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}

TEST(compareHands, straight){
	std::vector<Card> cardsHigher1 = readConfig("QCJDTC9C8C.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("JDTC9C8C7C.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsEqual = readConfig("QCJDTC9C8C.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("QCJSTC9C8C.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}

TEST(compareHands, threeOfKind){
	std::vector<Card> cardsHigher1 = readConfig("8C8D8H7D6C.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("8C8D8H7D5C.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsEqual = readConfig("8C8D8H7D6C.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("8S8S8C7C6D.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}
TEST(compareHands, twoPair){
	std::vector<Card> cardsHigher1 = readConfig("8S8S7C7C6D.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("8S8S7C7C5D.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsEqual = readConfig("8S8S7C7C6D.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("8S8S7H7C6D.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}
TEST(compareHands, onePair){
	std::vector<Card> cardsHigher1 = readConfig("8S8S5H7C6D.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("8S8S4H7C6D.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsEqual = readConfig("8S8S4H7C6D.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("8S8S4H7C6S.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}
TEST(compareHands, highCard){
	std::vector<Card> cardsHigher1 = readConfig("3S8S4H7C6S.cfg");
	PokerHand handHigher1 = PokerHand(cardsHigher1);
	std::vector<Card> cardsLower1 = readConfig("2S8S4H7C6S.cfg");
	PokerHand handLower1 = PokerHand(cardsLower1);
	EXPECT_GT(handHigher1.getValue(), handLower1.getValue());

	std::vector<Card> cardsEqual = readConfig("2S8S4H7C6S.cfg");
	PokerHand handEqual = PokerHand(cardsEqual);
	std::vector<Card> cardsEqual1 = readConfig("2S8S4H7C6C.cfg");
	PokerHand handEqual1 = PokerHand(cardsEqual1);
	EXPECT_EQ(handEqual.getValue(), handEqual1.getValue());
}

#endif // TST_NEWGTC_H
