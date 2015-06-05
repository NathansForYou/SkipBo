#ifndef _HAND_H
#define _HAND_H
#include "Pile.h"

// Class for player's hand
class Hand : public Pile {
	public:
		// Puts all cards in hand in order
		void order();	
		// Overloaded remove function
		Card remove(Card);
		// Prints save values for hand
		std::string saveHand() const;

};
#endif
