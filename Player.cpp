#include "Player.h"
#include <sstream>

using std::string; using std::vector; using std::ostringstream; using std::istream; using std::getline;

// Constructor that takes name
Player :: Player(string n):
	name(n), stack(), discardPiles(), hand(), game() { 
		Pile empty;
		for (int i = 0; i < DISCARD_NUM; i++) {
			discardPiles.push_back(empty);
		}	
	}

// Constructor that takes all parameters
Player :: Player(string n, const Pile &s, vector<Pile> d, Hand h):
	name(n), stack(s), discardPiles(d), hand(h), game() { }

std::string Player::getName() const{
	return name;
}

Player :: ~Player() { } // Need this to avoid error

// Gets the number of cards in the player's hand
int Player :: getHandSize() const {
	return hand.getSize();
}

// Gets the number of cards in the player's hand 
int Player :: getStackSize() const {
	return stack.getSize();
}

// Sets the game instance
void Player :: setGame(Game *g) {
	game = g;
}

// Plays the requested move, returning true if possible
// and false if invalid
bool Player :: play(const Move &m) {
	// If we're not taking from a valid pile
	if (m.fromType != 'H' && m.fromType != 'D' && m.fromType != 'S') {
		throw INVALID_ERROR;
	}

	// If we are taking from a valid pile
	if ((m.fromType == 'D' && discardPiles.at(m.fromIndex).getSize() != 0) || m.fromType == 'S') {
		
		// Set the current pile to the context
		Pile &currPile = (m.fromType == 'D') ? discardPiles.at(m.fromIndex) : stack;
		// Get the card on top of the current pile
		Card &fromTop = currPile.getTop();
		if (m.toType != 'B') {
			throw INVALID_ERROR;
		} else {
			Pile &bp = game->getBP(m.toIndex);
			if (bp.getSize() == 0) { // If the build pile is empty
				if (fromTop.getNumber(0) != 1) {	
					throw INVALID_ERROR;
				} else {
					fromTop.setNumber(1);
					bp.add(currPile.remove());
					dispMove(m);
				}
			} else {
				// Number of the top card on the to pile
				int toTopNum = bp.getTopNum();	
				// If we can play the card, do it
				if (fromTop.getNumber(toTopNum) == toTopNum + 1) {	
					fromTop.setNumber(toTopNum + 1);
					bp.add(currPile.remove());
					dispMove(m);
				} else {
					throw INVALID_ERROR;
				}
			}
		}
	} else if (m.fromType == 'H') {

		// If the hand card doesn't exist
		if (hand.getSize() <= m.fromIndex) {
			throw INVALID_ERROR;	
		}

		// If we are putting on a valid type of pile
		if (m.toType == 'B' || m.toType == 'D') {
			if (m.toType == 'B') {
				Pile &toPile = game->getBP(m.toIndex);

				// If we can play the card, do it
				if (hand.getCards().at(m.fromIndex).getNumber(toPile.getTopNum()) == toPile.getTopNum() + 1) {
					hand.getCards().at(m.fromIndex).setNumber(toPile.getTopNum() + 1);
					toPile.add(hand.remove(hand.getCards().at(m.fromIndex)));
					dispMove(m);
				} else {
					throw INVALID_ERROR;
				}


			} else {
				// Just place the card on the discard pile
				Pile &toPile = discardPiles.at(m.toIndex);
				toPile.add(hand.remove(hand.getCards().at(m.fromIndex)));
				dispMove(m);
				return false;
			}

		} else {
			throw INVALID_ERROR;
		}
	} else {
		throw INVALID_ERROR;
	}

	return true;
}

// Adds a card to the hand 
void Player :: addToHand(const Card c) {
	hand.add(c);
}

// Adds a vector of cards to the hand
int Player :: addToHand(const vector<Card> &v) {
	int numCards = hand.getSize();
	for (vector<Card>::const_iterator it = v.begin(); it != v.end(); it++) {
		addToHand(*it);
	}

	return numCards;
}

void Player :: addToStack(Card c){
	stack.add(c);
}

void Player :: dispMove(Move m) const{

	std::cout << name << " has played from ";
	if (m.fromType == 'S') {
		std::cout << m.fromType << 'P';
	} else {
		std::cout << m.fromType << m.fromIndex + 1;
	}
	std::cout << " to " << m.toType << m.toIndex + 1
		  << "." << std::endl;
}

// Formats the player as a string
string Player :: savePlayer() const {
	ostringstream output;
	output << "<Player>\n";
	output << "<name>\n";
	output << name << "\n";
	output << "</name>\n";
	output << "<Stack>\n";
	output << stack.savePile();
	output << "</Stack>\n";
	output << hand.saveHand();
	for (int i = 0; i < 4; i++){
		output << "<Pile>\n";
		output << discardPiles.at(i).savePile();
		output << "</Pile>\n";
	}
	output << "</Player>\n";
	return output.str();
}

// Loads the player from a file
void Player :: loadPlayer(istream &ifile) {
	string trash;
	
	ifile >> trash; // Eats the <Player> tag
	ifile >> trash; // Eats the <name> tag
	ifile.ignore(1, '\n'); // Gets rid of the newline character
	getline(ifile, name); // Gets the player's name
	ifile >> trash; // Eats the closing </name> tag
	stack.loadPile(ifile); // Loads the stack from the file
	hand.loadPile(ifile); // Loads the hand from the file
	// Loads the discard piles from the file
	for (int i = 0; i < DISCARD_NUM; i++) {
		discardPiles.at(i).loadPile(ifile);
	}

	ifile >> trash; // Eats the closing </Player> tag
}
