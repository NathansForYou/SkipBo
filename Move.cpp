#include "Move.h"
using std::string;

// Default constructor for a move
Move :: Move(): 
	isDiscard(true), fromType(), fromIndex(), toType(), toIndex() { }

// Takes "from" pile, "to" pile, type of move
Move :: Move(string f, string t) {
	isDiscard = (t.at(0) == 'D') ? true : false;
	fromType = f.at(0);
	fromIndex = f.at(1) - '0' - 1;
	toType = t.at(0);
	toIndex = t.at(1) - '0' - 1;
}
