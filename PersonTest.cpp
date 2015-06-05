#include "Person.h"
#include <cassert>

class PersonTest {

public:


static void testPerson() {

	Person p1;
	Person p2("Ben");
	Person p3("Joanne");

	// Testing constructors and basic return functions:
	assert(p1.getName() == "");
	assert(p2.getName() == "Ben");
	assert(p3.getName() == "Joanne");

	assert(p1.getStackSize() == 0);
	assert(p2.getStackSize() == 0);
	assert(p3.getStackSize() == 0);
	assert(p1.getHandSize() == 0);
	assert(p2.getHandSize() == 0);
	assert(p3.getHandSize() == 0);

	Card c1(1,false);
	Card c2(2, false);
	Card c3(13, true);
	Card c4(10, false);

	// Tests addToStack and getStackSize:
	p1.addToStack(c1);
	assert(p1.stack.getTopNum() == c1.getNumber());
	p2.addToStack(c2);
	assert(p2.stack.getTopNum() == c2.getNumber());
	p3.addToStack(c3);
	assert(p3.stack.getTopNum() == c3.getNumber());
	p3.addToStack(c2);
	assert(p3.stack.getTopNum() == c2.getNumber());
	p3.addToStack(c1);
	assert(p3.stack.getTopNum() == c1.getNumber());

	assert(p1.getStackSize() == 1);
	assert(p2.getStackSize() == 1);
	assert(p3.getStackSize() == 3);

	// Tests addToHand:
	std::vector<Card> v_c1;
	v_c1.push_back(c2);	
	v_c1.push_back(c1);	
	v_c1.push_back(c4);

	assert(p1.getHandSize() == 0);
	assert(p1.addToHand(v_c1) == 0);
	assert(p1.getHandSize() == 3);
	p1.hand.order();

	// Makes sure hand is in order:
	assert(p1.hand.getTopNum() == c4.getNumber());
	assert(p1.hand.remove(c4) == c4);
	assert(p1.hand.getTopNum() == c2.getNumber());
	assert(p1.hand.remove(c2) == c2);
	assert(p1.hand.getTopNum() == c1.getNumber());
	assert(p1.hand.remove(c1) == c1);
	p1.addToHand(c1);
	assert(p1.getHandSize() == 1);
	assert(p1.hand.getTopNum() == c1.getNumber());
	
}


};
int main(void) {
	std::cout << "Running Person tests..." << std::endl;
	// Tests:
	PersonTest::testPerson();
	std::cout << "Person tests complete!" << std::endl;
	return 0;
}
