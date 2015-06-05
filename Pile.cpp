#include "Pile.h"
using std::vector;
using std::string;
using std::ostringstream;
using std::istream;
using std::setw;
using std::setfill;

// Constructors
Pile :: Pile(): 
	cards() { }

Pile :: Pile(const Pile &p):
	cards(p.cards) { }

// Gets the number of cards in the pile
int Pile :: getSize() const {
	return cards.size();
}

// Gets all the cards
vector<Card> &Pile :: getCards() {
	return cards;
}

// Gets the card on top 
Card &Pile :: getTop() {
	return *(cards.end() - 1); 
}

// Const version of getTop
const Card Pile :: getTop() const {
	return *(cards.end() - 1);
}

// Returns the number of the card on top (0 if there is no card)
int Pile :: getTopNum() const {
	if (getSize() == 0) {
		return 0;
	} else {
		return getTop().getNumber();
	}
}

// Gets the top card in string form
string Pile :: getTopString() const {
	ostringstream retVal;
	retVal << setw(2) << setfill(' ');
	int topNum = getTopNum();

	if (topNum == 0) {
		retVal << "  ";
	} else if (topNum < 13) {
		retVal << topNum;
	} else {
		retVal << "SB";
	}

	return retVal.str();
}

// Adds a card to the pile
void Pile :: add(const Card c) {
	cards.push_back(c);
}

// Returns string for saving purposes
string Pile :: savePile() const {
	ostringstream output;
	output << "<size>\n";
	output << "\t" << getSize() << "\n";
	output << "</size>\n";
	
	for (int i = 0; i < getSize(); i++) {
		output << cards.at(i).saveCard();
	}

	return output.str();
}

// Loads pile from file
void Pile :: loadPile(istream &ifile) {
	string trash;
	int size;
	ifile >> trash; // Gets rid of the <Pile> tag
	ifile >> trash >> size >> trash; // Gets the number of cards to read
	Card c;
	// Reads all the cards
	for (int i = 0; i < size; i++) {
		c.loadCard(ifile);
		cards.push_back(c);
	}
	ifile >> trash; // Gets rid of the closing </Pile> tag
}

Pile &Pile :: operator=(Pile &p) {
	cards = p.cards;
	return *this;
}

// Removes card from the end of pile, returning the removed card
Card Pile :: remove() {
	Card c = *(cards.end() - 1);
	cards.pop_back();
	return c;
}
