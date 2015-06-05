#ifndef _GAME_H
#define _GAME_H

#include "Pile.h"
#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>

#define DEF_STACK_SIZE 20
#define NUM_BUILD_PILES 4
#define MAX_PLAYERS 6
#define MIN_PLAYERS 2
#define STD_ERROR "That's not a valid move"

class Player;
class UserInterface;

class Game {
	private:
		friend class UserInterface;
		std::vector<Player *> players; // Vector of all players
		Pile noPlay; //piles that are capped and moved out of play until reshuffle
		Deck deck; // Main deck of the game
		std::vector<Pile> buildPiles; // Build piles
		int stackSize; //Initial stack size for players
		int currentPlayer; //Index indicating the player whos turn is underway.

	public:
		Game(); // Default constructor
		void startGame(); //Initializes a game
		void startTurn(); //Starts a turn for a player
		void repeatTurn(bool); //Allows multiple moves
		Pile &getBP(int); // Returns a reference to the build pile indicated by the reference int.
		void endGame(std::string winner); //Ends program when a player win the game
		void save(std::string) const; //Saves the current instance of the game to a file
		void load(std::string); //Loads all necessary data from the file
		void draw();
};

#endif
