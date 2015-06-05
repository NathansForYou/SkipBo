#ifndef H_deck
#define H_deck
#include "Card.h"
#include "Pile.h"
#include <cstdlib>
#include <string>
#define MAX_DECK_SIZE 162

class Deck : public Pile
{
	public:
		Deck(); //builds deck at beginning, 162 cards
		Deck(const Pile &); //copy constructor
		void shuffle(); //randomizes card order
	
		std::string saveDeck() const;
		Deck &operator=(Pile &); //recreates deck from noPlay piles
};

#endif
