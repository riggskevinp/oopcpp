#include "card.h"
#include <iostream>
#include <stdexcept>

Card::Card(char suit, char face)
{
	switch(suit) {
	case('H'):{
		this->suit = 'H';
		break;
	}
	case('S'):{
		this->suit = 'S';
		break;
	}
	case('D'):{
		this->suit = 'D';
		break;
	}
	case('C'):{
		this->suit = 'C';
		break;
	}
	default:
		throw std::runtime_error("Not supported input");
	}

	if(static_cast<int>(face - '0') >= 2 && static_cast<int>(face - '0') < 10){
		this->face = static_cast<int>(face - '0') - 2;
	}
	else{
		switch(face){
		case('T'):{
			this->face = 8;
			break;
		}
		case('J'):{
			this->face = 9;
			break;
		}
		case('Q'):{
			this->face = 10;
			break;
		}
		case('K'):{
			this->face = 11;
			break;
		}
		case('A'):{
			this->face = 12;
			break;
		}
		default:
			throw std::runtime_error("Not supported input");
		}
	}
}
