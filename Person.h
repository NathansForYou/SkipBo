#ifndef _PERSON_H
#define _PERSON_H

#include "Player.h"
#include <string>

// Class that represents a human player (inherits from player class) in the game
class Person : public Player {
	
	public:
		// Default constructor
		Person(std::string s = "");
		bool isHuman() const;
		// Handles interaction between play from Player class and getting a move to try from UserInterface classs 
		bool move();

};

#endif

