#include "Pile.h"
#include "Card.h"
#include <iostream>
#include <cassert>
#include <vector>

using std::cout;
using std::endl;

// Tests the add function
Pile testAddAndGetCards() {
	Pile p;
	
	// Creates cards to play with
	Card c1(1); // Normal 1
	Card c2(2); // Normal 2
	Card c3(7); // Normal 7
	Card c4(12); // Normal 12
	Card sb(13, true); // Skipbo

	// Runs the add tests
	assert(p.getCards().size() == 0);
	p.add(c1);
	assert(p.getCards().at(0) == c1);
	p.add(c2);
	assert(p.getCards().at(1) == c2);
	p.add(c3);
	assert(p.getCards().at(2) == c3);
	p.add(sb);
	assert(p.getCards().at(3) == sb);
	p.add(c4);
	assert(p.getCards().at(4) == c4);
	assert(p.getCards().at(0) == c1); // Makes sure we're not changing stuff

	return p;
}

// Tests functions relating to getting the top card or its value
void testGetTops(Pile &p) {
	Card &c1 = p.getTop();
	Card sb(13, true); // Skipbo card
	assert(c1.getNumber() == 12);
	assert(p.getTopNum() == 12);
	assert(p.getTopString() == "12");

	// Verify that modifying the card changes the pile
	c1.setNumber(8);
	Card &c2 = p.getTop();
	assert(c2.getNumber() == 8);
	assert(p.getTopNum() == 8);
	assert(p.getTopString() == " 8");

	// Tests skipbo card
	p.add(sb);
	Card &c3 = p.getTop();
	// We use 13 to denote skipbos that haven't been played yet
	assert(c3.getNumber() == 13);
	assert(p.getTopNum() == 13);
	assert(p.getTopString() == "SB");	
}

// Tests getting the size of the pile
void testGetSize(Pile &p) {
	int size = p.getCards().size();
	assert(size == 6);
	assert(p.getSize() == size);
		
	Card c(10);
	p.add(c);
	assert(p.getSize() == size + 1);
}

// Tests removing cards from the pile
void testRemove(Pile &p) {
	int size = p.getSize();
	assert(size == 7);
	Card c = p.getTop();
	assert(c.getNumber() == 10);

	// Removes cards off the top of the pile
	p.remove();
	assert(p.getSize() == size - 1);
	assert(p.getTopString() == "SB");

	p.remove();
	assert(p.getSize() == size - 2);
	assert(p.getTopNum() == 8);

	size = p.getSize();
	for (int i = 0; i < size; i++) {
		p.remove();
	}

	assert(p.getSize() == 0);
}

int main(void) {
	cout << "Running Pile tests..." << endl;
	Pile p = testAddAndGetCards();
	testGetTops(p);
	testGetSize(p);
	testRemove(p);
	cout << "Pile tests complete!" << endl;

	return 0;
}
