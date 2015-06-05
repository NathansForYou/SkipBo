# Makefile for Intermediate Programming final project

CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O0 -g -fmax-errors=5
GPROF = -pg
GCOV = -fprofile-arcs -ftest-coverage

test: CardTest MoveTest PileTest HandTest DeckTest PersonTest
	@echo "Running tests..."	
	./CardTest
	./MoveTest
	./PileTest
	./HandTest
	./DeckTest
	./PersonTest

# recompiles tests with gcov on and reports the lines not tested
testgcov:
	make clean
	make CXXFLAGS="$(CXXFLAGS) $(GCOV)" test
	gcov *.cpp
	-@grep -n "#####" *.cpp.gcov

MoveTest: MoveTest.o Move.o
	$(CC) $(CXXFLAGS) Move.o MoveTest.o -o MoveTest

HandTest: HandTest.o Hand.o
	$(CC) $(CXXFLAGS) Card.o Pile.o Hand.o HandTest.o -o HandTest

DeckTest: Deck.o DeckTest.o
	$(CC) $(CXXFLAGS) Deck.o Card.o Pile.o DeckTest.o -o DeckTest

PersonTest: PersonTest.o Player.o Game.o 
	$(CC) $(CXXFLAGS) Person.o PersonTest.o Player.o UserInterface.o Card.o Game.o Pile.o Hand.o Computer.o Deck.o Move.o -o PersonTest

CardTest: Card.o CardTest.o
	$(CC) $(CXXFLAGS) Card.o CardTest.o -o CardTest
PileTest: Pile.o PileTest.o
	$(CC) $(CXXFLAGS) PileTest.o Card.o Pile.o -o PileTest

SkipBo: SkipBoMain.o Person.o Computer.o Game.o
	$(CC) $(CXXFLAGS) Card.o Pile.o Deck.o Move.o Hand.o UserInterface.o SkipBoMain.o Player.o Person.o Computer.o Game.o -o SkipBo

Game.o: Game.cpp Person.o Computer.o Deck.o UserInterface.o
Card.o: Card.cpp
Pile.o: Pile.cpp Card.o 
Deck.o: Deck.cpp Pile.o
Move.o: Move.cpp
Hand.o: Hand.cpp Pile.o
Player.o: Player.cpp Move.o Pile.o Hand.o
Person.o: Person.cpp Player.o 
Computer.o: Computer.cpp Player.o
UserInterface.o: UserInterface.cpp
PersonTest.o: PersonTest.cpp Person.o
SkipBoMain.o: SkipBoMain.cpp Game.o
PileTest.o: PileTest.cpp Pile.o
CardTest.o: CardTest.cpp Card.o
DeckTest.o: DeckTest.cpp Deck.o
MoveTest.o: MoveTest.cpp Move.o
HandTest.o: HandTest.cpp Hand.o

clean:
	rm -f a.out *~ *.o *.gcov *.gcda *.gcno gmon.out CardTest MoveTest DeckTest HandTest PlayerTest PersonTest ComputerTest PileTest SkipBo
