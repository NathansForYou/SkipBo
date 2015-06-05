#include "Card.h"
#include "Deck.h"
#include <cstdio>
#include <cassert>
#include <time.h>
#include <cstdlib>

void testConstructor() {

	Deck d; // Default constructor
	assert(d.getSize() == MAX_DECK_SIZE); // Checks if deck is the right size
	
	std::vector<Card> dek = d.getCards();

	int nums[13] = {};

	// Runs through the deck counting the number of times each card appears
	for (int i = 0; i < MAX_DECK_SIZE; i++) {
		nums[dek.at(i).getNumber()-1]++;
	}

	// Asserts every numbered card shows up 12 times and that there are 18 skipbos
	assert(nums[0] == 12);
	assert(nums[1] == 12);
	assert(nums[2] == 12);
	assert(nums[3] == 12);
	assert(nums[4] == 12);
	assert(nums[5] == 12);
	assert(nums[6] == 12);
	assert(nums[7] == 12);
	assert(nums[8] == 12);
	assert(nums[9] == 12);
	assert(nums[10] == 12);
	assert(nums[11] == 12);
	assert(nums[12] == 18);

}

void testOperator_and_Shuffle() {

	srand(5); // Seeds the random generator for expected order after shuffling
	Pile p;
	Card c1(1);
	Card c2(2);
	Card c3(3);
	Card c4(4);

	// p: 1->2->3->4->1
	p.add(c1);
	p.add(c2);
	p.add(c3);
	p.add(c4);
	p.add(c1);

	// Checks order of cards in p
	assert(p.getTopNum() == 1);
	p.remove();
	assert(p.getTopNum() == 4);
	p.remove();
	assert(p.getTopNum() == 3);
	p.remove();
	assert(p.getTopNum() == 2);
	p.remove();
	assert(p.getTopNum() == 1);
	p.remove();

	// Adds the cards in the same order again
	p.add(c1);
	p.add(c2);
	p.add(c3);
	p.add(c4);
	p.add(c1);

	Deck d; // Empty deck
	d = p; // Assigns p to d and shuffles -> order is changed
	assert(d.getTopNum() != 1);
	assert(d.getTopNum() == 3);
	d.remove();
	assert(d.getTopNum() == 4);
	d.remove();
	assert(d.getTopNum() != 3);
	assert(d.getTopNum() == 1);
	d.remove();
	assert(d.getTopNum() != 2);
	assert(d.getTopNum() == 1);
	d.remove();
	assert(d.getTopNum() != 1);
	assert(d.getTopNum() == 2);
	d.remove();
}

int main() {
	std::cout << "Running Deck tests..." << std::endl;
	testConstructor();
	testOperator_and_Shuffle();
	std::cout << "Deck tests passed!" << std::endl;
}
