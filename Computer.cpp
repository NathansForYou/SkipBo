#include "Computer.h"
using std::string;
using std::vector;

Computer :: Computer(string n): Player::Player(n) {
}

bool Computer :: isHuman() const { 
	return false;
}

// Generates a move from the computer
bool Computer :: move() {
	string sp = "SP";
	// Tries to play from stack first
	for (int i = 1; i <= NUM_BUILD_PILES; i++) {
		string bp = "B";
		Move m(sp, bp.append(1, i + '0'));
		try {	
			return play(m);
		} catch (char const *s) { }
	}

	// Tries to play from hand to build piles next
	for (int i = 1; i <= getHandSize(); i++) {
		for (int k = 1; k <= NUM_BUILD_PILES; k++) {
			string h = "H";
			string bp = "B";
			Move m(h.append(1, i + '0'), bp.append(1, k + '0'));
			try { 
				bool val = play(m);
				return val;
			} catch (char const *s) { }
		}
	}

	// Tries to go from discard to build piles next
	for (int i = 1; i <= DISCARD_NUM; i++) {	
		for (int k = 1; k <= NUM_BUILD_PILES; k++) {
			string d = "D";
			string bp = "B";
			Move m(d.append(1, i + '0'), bp.append(1, k + '0'));
			try {
				return play(m);
			} catch (char const *s) { }
		}
	}

	// Moves from hand to discard if no other options are available
	string h = "H";
	string d = "D";	
	Move m(h.append(1, getHandSize() + '0'), d.append(1, rand() % DISCARD_NUM + 1 + '0'));
	return play(m);
}


