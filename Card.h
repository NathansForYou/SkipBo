#ifndef _CARD_H
#define _CARD_H
#define SKIP_BO true
#define PILE_MAX 12
#include <sstream>
#include <fstream>
#include <string>

class Card {

	private:
		// Card is composed of a number and a bool indicating if it is a skipbo
		int number;
		bool type;

	public:
		// Constructos
		Card();
		Card(int num, bool type = !SKIP_BO);
		// Returns the number of the card
		int getNumber() const;
		// Returns the number of the card or the number of a given card (which is trying to be put on top of it) plus one if card is a skipbo
		int getNumber(int other) const;
		// Returns the type of the card
		bool getType() const;
		// Changes the number of the card (when a skipbo is placed)
		int setNumber(int new_num);

		// Returns string for saving purposes
		std::string saveCard() const;
	
		// Loads card from file
		void loadCard(std::istream &);

		bool operator==(const Card &) const; // Overloaded == operator 
		bool operator<(const Card &) const;  // Overloaded < operator
		bool operator>(const Card &) const;  // Overloaded > operator
};
#endif
