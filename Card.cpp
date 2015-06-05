#include "Card.h"
using std::string;
using std::ostringstream; using std::istream;

// Default constructor for card
Card :: Card(): number(-1), type(!SKIP_BO) { }

// Constructor for card that takes number and type
Card :: Card(int num, bool t): number(num), type(t) { }

// Returns the number of the card
int Card :: getNumber() const {
	return number;
}

// Returns the number of the card or the number of a given card (which is tryingto be put on top of it) plus one if card is a skipbo.
int Card :: getNumber(int other) const {

	if (type == SKIP_BO) {
		return other + 1;
	}
	return number;
}

// Returns the type of the card (true if skipbo, false if not)
bool Card :: getType() const{
	return type;
}

// Sets the card number to a different given value. Returns the new value.
int Card :: setNumber(int new_num) {
	number = new_num;
	return number;
}

// Returns string for saving purposes
string Card :: saveCard() const{
	ostringstream output;
	output << "<Card>\n";
	output << "\t<type>\n";
	output << "\t\t" << type << "\n";
	output << "\t</type>\n";
	output << "\t<number>\n";
	output << "\t\t" << number << "\n";
	output << "\t</number>\n";
	output << "</Card>\n";

	return output.str();
}

// Loads card from file
void Card :: loadCard(istream &ifile) {
	string trash;
	ifile >> trash; // Gets rid of the <Card> tag
	ifile >> trash >> type >> trash; // Gets the type 
	ifile >> trash >> number >> trash; // Gets the card number
	ifile >> trash; // Gets rid of the closing </Card> tag
}

// Overloaded < operator for cards
bool Card :: operator<(const Card &c) const {
	return (number < c.getNumber(number)); 
}

// Overloaded > operator for cards
bool Card :: operator>(const Card &c) const {
	return !(number < c.getNumber(number));
}

// Overloaded == operator for cards
bool Card :: operator==(const Card &c) const {
	return (number == c.getNumber());
}
