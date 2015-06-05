#ifndef _MOVEOURS_H
#define _MOVEOURS_H
#include <string>

class Move {
	public:
		bool isDiscard; // True if a discard play
		char fromType; // From pile type
		int fromIndex; // From pile index
		char toType; // To pile type
		int toIndex; // To pile index

		Move(); // Default constructor
		Move(std::string, std::string); // Full constructor
};

#endif
