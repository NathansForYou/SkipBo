#ifndef _USER_INTERFACE_H
#define _USER_INTERFACE_H

#include "Game.h"
#include "Move.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define MAX_BUFFER_LEN 500
#define BOARD_WIDTH 105
#define BOARD_HEIGHT 21
#define MAT_WIDTH 32
#define MAT_HEIGHT 5
#define MAT_SPACE 4
#define DECK_WIDTH 7
#define DECK_HEIGHT 7
#define DECK_ROW 7
#define DECK_COL 40
#define BUILD_WIDTH 10
#define BUILD_HEIGHT 5
#define BUILD_ROW 8
#define BUILD_COL 51
#define MIDDLE_SPACE 11
#define CLEAR_BUFFER cin.ignore(MAX_BUFFER_LEN, '\n');

class UserInterface {
	private:
		// Appropriately interprets user input with limited error handling
		static std::string getInput();

	public:
		// Prints out a main menu for the game and gets initial input (before game begins) from user
		static void mainMenu(Game &);

		// Displays the full gameboard
		static void display(Game &);

		// Adds a 2d array to the board at specific indices
		static void addToBoard(wchar_t board[BOARD_HEIGHT][BOARD_WIDTH], int row, int col, wchar_t **addition, int height, int width);

		// Creates a single player's mat (depends on top/bottom)
		static wchar_t **createPlayerMat(Player *, bool isTop);
		
		// Creates the deck
		static wchar_t **createDeck();
	
		// Creates the build piles in the middle
		static wchar_t **createBuildPiles(Game &);

		// Adds stars to indicate which player's turn it currently is
		static void addTurnIndicator(wchar_t board[BOARD_HEIGHT][BOARD_WIDTH], int p_index);

		// Prints out a player's hand
		static void displayPlayerHand(Player *p);

		// Using getInput, returns a possibly valid move from player input (also does some error handling).
		static Move getMove(Game &);

		// Gets the row and column indices at which to place a player
		static int getPlayerRow(int pNum);
		static int getPlayerCol(int pNum);

		// Prompts the user to save the game
		static void promptSave(Game &);

		// Prints the game's winner
		static void printWinner(std::string &);
};
#endif
