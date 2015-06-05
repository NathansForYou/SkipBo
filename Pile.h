#ifndef _PILE_H
#define _PILE_H
#include "Card.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

class UserInterface;
class Pile {

	protected:
		friend class UserInterface;
		// Contains the main cards of the pile
		std::vector<Card> cards;

	public:
		// Constructors
		Pile();
		Pile(const Pile &p);
		// Gets the vector of cards
		std::vector<Card> &getCards();
		// Gets the top card from the pile
		Card &getTop();
		const Card getTop() const;
		// Gets the number of the top card
		int getTopNum() const;
		// Gets the top number in string format (SB for skip-bo)
		std::string getTopString() const;
		// Gets the number of cards in the pile
		int getSize() const;
		// Adds a card to the pile
		void add(const Card c);
		// Removes a card from the pile
		virtual Card remove();

		// Return string for saving purposes
		std::string savePile() const;

		// Loads pile from file
		void loadPile(std::istream &);
		Pile &operator=(Pile &);

};
#endif
