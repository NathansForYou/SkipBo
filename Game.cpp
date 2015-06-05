#include "Game.h"
#include "Player.h"
#include "UserInterface.h"
#include "Person.h"
#include "Computer.h"
#include <time.h>
#include <fstream>
#define CONGRATULATIONS_SIZE 30

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ofstream;

// Default constructor for Game
Game :: Game(): 
	players(), noPlay(), deck(), buildPiles(), stackSize(DEF_STACK_SIZE), currentPlayer() {
	
	// Creates an empty pile in each index of the buildPiles vector
	Pile bp;
	for (int i = 0; i < NUM_BUILD_PILES; i++) {
		buildPiles.push_back(bp);
	}
}

void Game :: startGame() {
	setlocale(LC_ALL, "");
	try {
		UserInterface::mainMenu(*this);	
		//DEAL CARDS
		for (int i = 0; i < (int) players.size(); i++){
			players.at(i)->setGame(this);
			for (int j = 0; j < stackSize; j++){
				players.at(i)->addToStack(deck.remove());
			}
		}
	} catch (string fName) {
		load(fName);
	}

	try {
		while (true) {
			// Ask if the player would like to save		
			startTurn();
			
			// Controls the order of the turns, this is necessary
			// Because of the order in which we populate the game board
			// Based on the number of players
			//
			// Preferred move order: 4<-2<-6
			// 		  	 |     |
			// 		    	 3->1->5		
			switch (currentPlayer) {
				case 0:
					switch(players.size()) {
						case 2:
						case 3:
						case 4:
							currentPlayer = 1; break;
						case 5:
						case 6:
							currentPlayer = 4; break;
					} break;
				case 1: 
					switch(players.size()) {
						case 2:
							currentPlayer = 0; break;
						case 3:
							currentPlayer = 2; break;
						case 4:
						case 5:
						case 6:
							currentPlayer = 3; break;
					} break;
				case 2:
					currentPlayer = 0; break;
				case 3:
					currentPlayer = 2; break;
				case 4:
					if (players.size() == 6) {
						currentPlayer = 5;
					} else {
						currentPlayer = 1;
					} break;
				case 5: 
					currentPlayer = 1;
			}	
		}

	} catch (int e) {
		endGame(players.at(currentPlayer)->getName());
	}
}

void Game :: startTurn() {
	draw();
	repeatTurn(true);
}	
	
// Allows a player to make multiple moves
void Game :: repeatTurn(bool firstMove) {
	Player &p = *(players.at(currentPlayer));
	if (p.isHuman()) {
		UserInterface::display(*this);
		cout << "\n\n";
		UserInterface::displayPlayerHand(&p);
		if (firstMove) {
			UserInterface::promptSave(*this);
		}
	}

	try {
		// Lets player make as many moves as he wants until discard
		while (p.move() != false) {	
			// If any of the build piles are full, put them into the noPlay pile
			for (int i = 0; i < NUM_BUILD_PILES; i++) {
				if (buildPiles.at(i).getSize() == PILE_MAX) {
					for (int k = 0; k < PILE_MAX; k++) {	
						// Reset the number of skipbos
						Card c = buildPiles.at(i).remove();
						c.setNumber(c.getNumber(12));				
						noPlay.add(c);
					}
				}
			}
			if (p.isHuman()) {
				UserInterface::display(*this);
				cout << "\n";
				UserInterface::displayPlayerHand(&p);
			}
			if (p.getHandSize() == 0) {
				draw();
			}
			//check sock pile->ends game if empty
			if (p.getStackSize() == 0) {
				throw(1);
			}
		}
	} catch (char const *e) {
		cout << STD_ERROR << ", " << p.getName() << "!" << endl;	
		repeatTurn(false);
	}	
}

// Returns a reference to the build pile called by the index argument
Pile & Game :: getBP(int index) {
	return buildPiles.at(index);
}

// Loads the game from a save file
void Game :: load(string fName) {
	ifstream ifile(fName, std::ios::in);
	string trash;
	int numPlayers;
	bool isHuman;
	
	ifile >> trash >> currentPlayer >> trash; // Loads in the current player number, disregarding style tags in file
	ifile >> trash >> numPlayers >> trash; // Loads in the number of players, disregarding style tags in file
	ifile >> trash; // Eats <Players> tag
	for (int i = 0; i < numPlayers; i++) {
		ifile >> trash >> isHuman >> trash; // Checks if the player is human or not
		Player *x;	
		if (isHuman) {
			x = new Person;
		} else {
			x = new Computer;
		}	
		x->loadPlayer(ifile); // Loads in each player
		x->setGame(this);
		players.push_back(x); // Adds the pointer to the vector of player pointers in game
	}	
	ifile >> trash; // Eats the "</Players>" tag
	deck.loadPile(ifile); // Loads the deck
	noPlay.loadPile(ifile); // Loads the noPlay pile
	ifile >> trash; // Eats the "<buildPiles>" tag
	for (int i = 0; i < NUM_BUILD_PILES; i++) {
		buildPiles.at(i).loadPile(ifile); // Reads in each build pile
	}
	ifile.close();
}

// Saves the current game state to a file using pseudo XML
void Game :: save(string fName) const {
	ofstream ofile(fName, std::ios::out);
	ofile << "<currentPlayer>\n\t" << currentPlayer << endl;
	ofile << "</currentPlayer>\n";
	ofile << "<numPlayers>\n\t" << players.size() << endl;
	ofile << "</numPlayers>\n";
	ofile << "<Players>\n";
	for (int i = 0; i < (int) players.size(); i++) {
		ofile << "<isHuman>\n\t" << players.at(i)->isHuman() << "\n</isHuman>\n";
		ofile << (*players.at(i)).savePlayer();
	}
	ofile << "</Players>\n";
	ofile << deck.saveDeck();
	ofile << "<noPlay>\n" << noPlay.savePile() << "</noPlay>\n";
	ofile << "<buildPiles>\n";
	for (int i = 0; i < NUM_BUILD_PILES; i++) {
		ofile << "<Pile>\n" << buildPiles.at(i).savePile() << "</Pile>\n";
	}
	ofile << "</buildpiles>\n";
	ofile.close();
}

// Displays the end game message and prompts to start a new game
void Game :: endGame(string winner) {
	UserInterface :: printWinner(winner);
	cout << "\n\n" << "Would you like to start a new game (yes/no)? ";

	// Checks if new game will be played
	string input;
	while (cin >> input && input != "yes" && input != "no") {
		CLEAR_BUFFER;
		cout << "Please enter either \"yes\" or \"no\": ";
	}
	CLEAR_BUFFER;
	
	// Cleans up allocated memory for the players
	for (int i = 0; i < (int) players.size(); i++) {
			delete players.at(i);
	}

	if (input == "yes") {	
		srand(time(NULL));
		Game game;
		game.startGame();	
	} else {
		cout << "Goodbye!" << endl;
	}
}

// Draws cards from the deck, placing them in the player's hand
void Game :: draw() {
	int newCards = 5 - players.at(currentPlayer)->getHandSize();
	for (int i = 0; i < newCards; i++){
		if (deck.getSize() == 0){
			deck = noPlay; //overloaded =, will return the new shuffled deck
			for (int k = 0; k < noPlay.getSize(); k++){
				noPlay.remove();
			}
		}	
		players.at(currentPlayer)->addToHand(deck.remove());
	}
}

