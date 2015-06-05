#include "Hand.h"
#include <cassert>

void testHand() {

	Hand h1;
	Card c1(1); // Normal 1
	Card c2(2);// Normal 2
	Card c3(3);// Normal 3
	Card c4(4);// Normal 4
	Card c11(11);// Normal 11
	Card c12(12);// Normal 12
	Card sb(13, SKIP_BO); // Skipbo

	h1.add(c1);
	assert(h1.getTopNum() == c1.getNumber()); //Checks if card was added

	h1.add(c3);
	h1.add(c2);
	h1.order(); 

	assert(h1.getTopNum() == c3.getNumber()); // C3 should be at the top after it gets ordered

	h1.add(sb);
	h1.add(c12);
	h1.add(c11);
	h1.order(); 

	assert(h1.getTopNum() == sb.getNumber()); // Skipbos always at the top

	h1.add(c4);
	assert(h1.getTopNum() == c4.getNumber()); // Added new card, out of order
	h1.order();
	assert(h1.getTopNum() == sb.getNumber()); // Skipbos always at the top

	// Testing the remove function:
	assert(h1.remove(c4) == c4);
	assert(h1.remove(sb) == sb);
	assert(h1.remove(c11) == c11);

	// Adding a new card out of order
	h1.add(c3);
	h1.order();
	// Removing all cards and checking if hand is fully ordered:
	assert(h1.getTopNum() == c12.getNumber());
	assert(h1.remove(c12) == c12);
	assert(h1.getTopNum() == c3.getNumber());
	assert(h1.remove(c3) == c3);
	assert(h1.getTopNum() == c3.getNumber()); // C3 remains at end because two c3 cards were added
	assert(h1.remove(c3) == c3);
	assert(h1.getTopNum() == c2.getNumber());
	assert(h1.remove(c2) == c2);
	assert(h1.getTopNum() == c1.getNumber());
	
	
}

int main() {

	std::cout << "Running Hand tests..." << std::endl;
	testHand();
	std::cout << "Hand tests passed!" << std::endl;
	return 0;
}
