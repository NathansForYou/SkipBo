#include "Person.h"
#include "UserInterface.h"

using std::string;
 
// Default constructor
Person :: Person(string s): Player::Player(s) {
}

bool Person :: isHuman() const {
	return true;
}

// Returns false if requested move from UserInterface is not possible and true if it is (also executes move in the process)
bool Person :: move() {
	Move m = UserInterface::getMove(*game); // Gets a move request
	return play(m); //Tries to execute it and returns result
}
