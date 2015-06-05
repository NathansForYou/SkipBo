#include "Move.h"
#include <iostream>
#include <cassert>

using std::cout; using std::endl;

// Tests the Move constructor (makes sure the strings are being parsed correctly)
void constructTest() {
	
	// Hand to build
	Move m("H1", "B2");
	assert(m.fromType == 'H');
	assert(m.fromIndex == 0);
	assert(m.toType == 'B');
	assert(m.toIndex == 1);

	// Hand to discard
	Move m1("H2", "D4");
	assert(m1.fromType == 'H');
	assert(m1.fromIndex == 1);
	assert(m1.toType == 'D');
	assert(m1.toIndex == 3);

	// Stack to build
	Move m2("SP", "B4");
	assert(m2.fromType == 'S');
	// We don't use fromIndex for stack moves
	assert(m2.toType == 'B');
	assert(m2.toIndex == 3);
}

int main(void) {
	cout << "Running Move tests..." << endl;
	constructTest();
	cout << "Move tests passed!" << endl;
	return 0;
}
