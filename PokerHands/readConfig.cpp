#include "readConfig.h"
#include "card.h"

#include <iostream>
#include <vector>

std::vector<Card> readConfig(const std::string &str)
{
	libconfig::Config cfg;
	try
	{
		cfg.readFile(str);
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
		return cardVec;
	}
	catch(const libconfig::SettingNotFoundException &nfex)
	{
		std::cerr << "SettingNotFound " << nfex.what() << nfex.getPath() << std::endl;
	}
}
