#include "Hand.h"
using std::vector; 

// Orders the cards in the hand
void Hand::order()
{
	std::sort(cards.begin(), cards.end());
}

// Removes a card from the hand, resizing the vector and returning the removed card.
Card Hand::remove(Card c)
{
	vector<Card>::iterator it = find(cards.begin(), cards.end(), c);
	cards.erase(it);
	return c;
}

std::string Hand::saveHand() const {
	std::string output;
	output += "<Hand>\n";
	output += savePile();
	output += "</Hand>\n";
	return output;
}

