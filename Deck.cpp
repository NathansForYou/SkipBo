#include "Deck.h"

using std::string;

// Initial default constructor, only used when starting game
Deck :: Deck() {
	// Create 162 cards, 144 random, 18 Skip-Bo
	for (int i = 1; i <= MAX_DECK_SIZE; i++){
		if (i > PILE_MAX * PILE_MAX) {
			Card card(PILE_MAX + 1, SKIP_BO);
			add(card);
		} else {
			Card card(i % PILE_MAX + 1, !SKIP_BO);
			add(card);
		}	
	}
	
	this->shuffle();
}

// Copy constructor for deck
Deck :: Deck(const Pile &p): Pile::Pile(p) {
	shuffle();
}

// Overloaded assignment operator for deck
Deck &Deck :: operator=(Pile &p) {
	cards = p.getCards();
	shuffle();
	return *this;
}

// Randomize order of current deck
void Deck :: shuffle() //randomize order of current deck
{
	int index;
	for (int i = 0; i < getSize(); i++){
		index = rand() % cards.size();
		Card temp = cards.at(index);
		cards.at(index) = cards.at(i);
		cards.at(i) = temp;
	}
}

// Returns string for saving purposes
string Deck :: saveDeck() const{
	string output;
	output += "<Deck>\n";
	output += savePile();
	output += "</Deck>\n";

	return output;
}
