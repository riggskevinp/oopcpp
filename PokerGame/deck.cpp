#include "deck.h"
#include <chrono>
#include <cstdlib>
#include <algorithm>


Card Deck::dealCard()
{
	return deckOfCards.at(currentIndex++);
}

void Deck::shuffle()
{
	currentIndex = 0;
	std::srand(static_cast<size_t>(std::chrono::system_clock().now().time_since_epoch().count()));
	std::random_shuffle(deckOfCards.begin(), deckOfCards.end(),[&](int i){
							return std::rand() % i;
	});

}
