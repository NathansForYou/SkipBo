#include "Card.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

// Tests constructor for Card
void testConstruct() {
	Card c(12);
	Card d(12, !SKIP_BO); // Testing explicit argument
	Card e(11);
	Card f(1);
	assert(f < e);
	assert(e < d);
	assert(e < c);
	assert(!(f == d));
	assert(c == d);
	Card sb(13, SKIP_BO); // Tests making a skipbo
	assert(!(sb == d));
}

// Test getter functions for Card
void testGetters() {
	Card c1(1);
	Card c2(2);
	Card c3(3);
	Card c7(7);
	Card c12(12);
	Card sb(13, SKIP_BO);

	assert(c1.getNumber() == 1);
	assert(c2.getNumber() == 2);
	assert(c3.getNumber() == 3);
	assert(c7.getNumber() == 7);
	assert(c12.getNumber() == 12);
	
	// Makes sure we are not falsifying card numbers when passed a number
	assert(c1.getNumber(2) != 3);
	assert(c7.getNumber(3) != 4);
	assert(c12.getNumber(10) == 12);
	
	// Tests simulation of skip-bo card's number (when we're trying to place it)
	assert(sb.getNumber(10) == 11);
	assert(sb.getNumber(0) == 1);
	assert(sb.getNumber(5) == 6);
}

// Tests the setNumber function for Card
void testSetNumber() {
	// Testing normal card
	Card c1(10);
	assert(c1.getNumber() == 10);
	assert(c1.setNumber(1) == 1);
	assert(c1.getNumber() == 1);
	assert(c1.getNumber(5) == 1);
	assert(c1.setNumber(5) == 5);
	assert(c1.getNumber() == 5);
	// Testing skipbo
	Card sb(13, SKIP_BO);
	assert(sb.getNumber() == 13);
	assert(sb.getNumber(5) == 6); // Testing virtual number of skipbo
	assert(sb.setNumber(12) == 12);
	assert(sb.getNumber() == 12);
	// Making sure skipbo can still act as any number (for when it is reshuffled)
	assert(sb.getNumber(8) == 9);
}

// Tests the overloaded operators for Card
void testOperators() {
	Card c1(1);
	Card sb1(1, SKIP_BO);
	Card c1dup(1);
	Card c2(2);
	Card c5(5);
	Card c9(9);
	Card c12(12);
	Card sb(13, SKIP_BO);

	// Tests for < operator
	assert(c1 < c9);
	assert(c2 < c9);
	assert(c9 < sb); // This is the behavior we defined, skipbos are always greater
	assert(c12 < sb); 
	assert(c5 < c12);

	// Tests for > operator
	assert(c9 > c1);
	assert(c5 > c2);
	assert(sb > c5);
	assert(c12 > c9);
	assert(c2 > c1);

	// Tests for == operator
	assert(c1 == c1dup);
	assert(c1 == sb1); // This is the behavior we defined, == ignores type
	assert(!(c1 == c2));
	assert(!(c5 == c9));
}

int main(void) {
	cout << "Running Card tests..." << endl; 
	testOperators();
	testConstruct();
	testGetters();
	testSetNumber();
	cout << "Card tests complete!" << endl;
	return 0;
}
