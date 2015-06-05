#include "UserInterface.h"
#include "Person.h"
#include "Computer.h"
#include <iomanip>
#include <cstdio>

using std::cout;
using std::wcout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void UserInterface :: mainMenu(Game &g) {

	// Initial statement to user
	cout << "\n\n"
	     << "Hello, and welcome to SkipBo! This game should be run with a minimum screen width of 104 characters." << endl
	     << "At the beginning of your turn, just type \"save file\" to save the current game state to a file of your choice." << endl << endl
	     << "Would you like to load a pre-existing game?" << endl
	     << "Please type \"yes\" or \"no\": ";

	// Determines whether or not the user wants to load a file
	string input;
	while (cin >> input && input != "yes" && input != "no") {
		CLEAR_BUFFER;
		cout << "Please enter either \"yes\" or \"no\": ";
	}
	
	CLEAR_BUFFER;

	if (input == "yes") {
		cout << "Please enter the game file you want to load: ";
		while (cin >> input) {
			CLEAR_BUFFER;
			std::ifstream ifile(input, std::ifstream::in);
			if (ifile.is_open()) {
				ifile.close();
				break;
			}
			cout << "Please enter a valid game file: ";
		} 
		// Throw an exception with the name of the file
		// If we want to load the file
		throw input;
	}

	// Initialize game using user input
	cout << endl << "Starting new game!" << endl << endl
	     << "Please enter total number of players (include robots): ";

	int numPlayers;
	while (cin >> numPlayers && (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS)) {
		CLEAR_BUFFER;
		cout << "Please enter valid number of players (2 to 6)!: ";
	}
	CLEAR_BUFFER;

	cout << "Please enter total number of human players: ";
	int numHumans;
	while (cin >> numHumans && (numHumans < 0 || numHumans > numPlayers)) {
		CLEAR_BUFFER;
		cout << "Please enter valid number of human players!: ";
	}
	CLEAR_BUFFER;

	string currPlayer;	

	vector<string> playerVector;
	 // Gets all player names, pushes to a vector
	for (int i = 0; i < numPlayers; i++) {
		cout << "Please enter name of player " << i + 1 << ": ";
		while (getline(cin, currPlayer, '\n')) {
			if (find(playerVector.begin(), playerVector.end(), currPlayer) == playerVector.end()) {
				break;
			}
			cout << "You've already used that name!" << endl;
			cout << "Please enter name of player " << i+1 << ": ";
		}
		playerVector.push_back(currPlayer);	
	}
	
	cout << "Please enter the number of cards in each stack: ";
	int stackSize;
	int maxStackSize = (MAX_DECK_SIZE - 5 * numPlayers) / numPlayers;
	while (cin >> stackSize && (stackSize < 1 || stackSize > maxStackSize)) {
		CLEAR_BUFFER;
		cout << "Invalid number of cards! Please choose a number between 1 and " 
		     << maxStackSize << endl
		     << "Please enter the number of cards in each stack: ";
	}
	cout << "\n";
	cout << "Dealing cards..." << endl;
	CLEAR_BUFFER;
	
	/*START BUILDING THE GAME*/
	g.stackSize = stackSize;

	for (int i = 0; i < numPlayers; i++) {
		Player *x;
		if (i < numHumans) {
			x = new Person(playerVector.at(i));
		}
		else {
			x = new Computer(playerVector.at(i));
		}	
		g.players.push_back(x);	
	}
	g.currentPlayer = 0;
}

// Gets a two character input code from the user
string UserInterface :: getInput() {
	string input;
	string errorMessage = "That's not a valid card";
	cin >> input;
	cin.ignore(MAX_BUFFER_LEN, '\n');
	if (input.length() == 2) {
		switch (input.at(0)) {
			case 'H':
				if (input.at(1) - '0' <= 0 || input.at(1) - '0' > 5) {	
					throw errorMessage;
				} break;
			case 'S':
				if (input.at(1) != 'P') {
					throw errorMessage;
				} break;	
			case 'B':
				if (input.at(1) - '0' <= 0 || input.at(1) - '0' > 4) {
					throw errorMessage;
				} break;
			case 'D':
				if (input.at(1) - '0' <= 0 || input.at(1) - '0' > 4) {
					throw errorMessage;
				} break;
			default:
				throw errorMessage;
				break;
		}	
	} else {
		throw errorMessage;
	}

	return input;
}

// Gets a move from the player 
Move UserInterface :: getMove(Game &g) {
	string currName = g.players.at(g.currentPlayer)->name;
	cout << currName << "'s move: Enter a card to place-> ";
	string fromInput, toInput;

	bool success = false;
	
	// Get the from field
	while (!success) {
		try { 
			fromInput = UserInterface::getInput(); 
			success = true;
		} catch(string err) { 
			cout << err << ", " << currName << "!" << endl; 
			cout << currName << "'s move: Enter a card to place-> ";
		}
	}
	
	success = false;
	cout << currName << "'s move: Enter where to put it-> ";

	// Get the from field
	while (!success) {
		try { 
			toInput = UserInterface::getInput(); 
			success = true;
		} catch(string err) { 
			cout << err << ", " << currName << "!" << endl; 
			cout << currName << "'s move: Enter where to put it-> ";
		}
	}
		
	// Creates the move from the input
	Move newMove(fromInput, toInput);
	
	return newMove;
}

// Displays the full gameboard
void UserInterface :: display(Game &g) {
	// Creates the board and populates it with the players
	wchar_t board[BOARD_HEIGHT][BOARD_WIDTH];
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int k = 0; k < BOARD_WIDTH; k++) {
			board[i][k] = ' ';
		}
	}

	for (int i = 0; i < (int) g.players.size(); i++) {
		// Gets the current player's mat and adds it to the board
		wchar_t **pmat = createPlayerMat(g.players.at(i), !((i + 1) % 2));
		addToBoard(board, getPlayerRow(i + 1), getPlayerCol(i + 1), pmat, MAT_HEIGHT, MAT_WIDTH);	
		delete[] pmat;
	}
	
	wchar_t **deck = createDeck();
	addToBoard(board, DECK_ROW, DECK_COL, deck, DECK_HEIGHT, DECK_WIDTH);
	delete[] deck;
	
	wchar_t **buildPiles = createBuildPiles(g);
	addToBoard(board, BUILD_ROW, BUILD_COL, buildPiles, BUILD_HEIGHT, BUILD_WIDTH);
	delete[] buildPiles;

	setlocale(LC_ALL, "");
	addTurnIndicator(board, g.currentPlayer);	
	cout << endl;
	// Prints the board
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		board[i][BOARD_WIDTH - 1] = '\0';
		printf("%ls\n", board[i]);
	}
}

// Adds a 2d array to the board at specific indices
void UserInterface :: addToBoard(wchar_t board[BOARD_HEIGHT][BOARD_WIDTH], int row, int col, wchar_t **addition, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			board[row + i][col + k] = addition[i][k];
		}
		delete[] addition[i]; // Deletes the addition
	}
}

// Creates the deck
wchar_t **UserInterface :: createDeck() {
	wchar_t **deck = new wchar_t*[DECK_HEIGHT];

	// Loops through all characters of deck
	for (int i = 0; i < DECK_HEIGHT; i++) {
		deck[i] = new wchar_t[DECK_WIDTH];
		for (int k = 0; k < DECK_WIDTH; k++) {	
			if (k > 0 && k < DECK_WIDTH - 1) {
				if (i == 0) {
					deck[i][k] = '_';
				} else if (i < DECK_HEIGHT - 1) {	
					deck[i][k] = L'\u2592';
				} else { 
					deck[i][k] = L'\u203E';
				}
			} else if (i > 0 && i < DECK_HEIGHT - 1) {
				deck[i][k] = '|';
			} else {
				deck[i][k] = ' ';
			}
		}	
	}
	return deck;
}

// Creates the build piles in the middle
wchar_t **UserInterface :: createBuildPiles(Game &g) {
	wchar_t **buildPiles = new wchar_t*[BUILD_HEIGHT];
	
	int pileNum = 0;
	for (int i = 0; i < BUILD_HEIGHT; i++) {
		buildPiles[i] = new wchar_t[BUILD_WIDTH];
		// Initializes each character to ' '
		for (int k = 0; k < BUILD_WIDTH; k++) {
			buildPiles[i][k] = ' ';
		}

		// Constructs the build piles
		for (int k = 0; k < BUILD_WIDTH; k++) {	
			if ((i == 1 || i == BUILD_HEIGHT - 1) && (k == 0 || k == BUILD_WIDTH - 4)) {	
				buildPiles[i][k] = '[';
				buildPiles[i][k + 1] = g.buildPiles.at(pileNum).getTopString().at(0);
				buildPiles[i][k + 2] = g.buildPiles.at(pileNum).getTopString().at(1);
				pileNum++;
				buildPiles[i][k + 3] = ']';
			} else if ((i == 0 || i == BUILD_HEIGHT - 2) && (k == 1 || k == BUILD_WIDTH - 3)) {
				buildPiles[i][k] = 'B';
				buildPiles[i][k + 1] = pileNum + (k/(BUILD_WIDTH - 3))+ 1 + '0';
			} 
		}	
	}
	
	return buildPiles;
}

// Creates a 2d string containing a single player's mat
wchar_t **UserInterface :: createPlayerMat(Player *p, bool isTop) {

	// Allocates and initializes the player's mat
	wchar_t **mat = new wchar_t*[MAT_HEIGHT];
	for (int i = 0; i < MAT_HEIGHT; i++) {
		mat[i] = new wchar_t[MAT_WIDTH];
		for (int k = 0; k < MAT_WIDTH; k++) {
			mat[i][k] = ' ';
		}
	}

	// Creates the formatting for the mat, including pile headers
	int rowNum = isTop ? 1 : 0;
	
	// Displays stack pile
	mat[rowNum + 1][3] = 'S';
	mat[rowNum + 1][4] = 'P';
	string spNum = p->stack.getTopString();
	mat[rowNum + 2][3] = spNum.at(0);
	mat[rowNum + 2][4] = spNum.at(1);
	
	// Writes the name to the mat
	string name = p->getName();
	int nameStart = (MAT_WIDTH - name.size()) / 2;
	for (int i = 0; i < (int) name.size(); i++) {
		mat[isTop ? 0 : MAT_HEIGHT - 1][nameStart + i] = name.at(i);
	}

	for (int i = 0; i < MAT_WIDTH; i++) {
		if (i >= 9 && (i - 9) % 6 == 0) {
			// Writes the discard piles to the mat	 
			mat[rowNum + 1][i] = 'D';
			mat[rowNum + 1][i + 1] = (i - 9) / 6 + 1 + '0';

			// Writes the card values to the mat
			string cardNum = (p->discardPiles.at((i - 9) / 6)).getTopString();
			mat[rowNum + 2][i] = cardNum.at(0);
			mat[rowNum + 2][i + 1] = cardNum.at(1);
		}
	
		// Writes the brackets for the cards
		else if (i >= 2 && (i - 2) % 6 == 0) {
			mat[rowNum + 2][i] = '[';
			mat[rowNum + 2][i + 3] = ']';
		}	
			
		mat[rowNum][i] = '-';
		mat[rowNum + 3][i] = '-';
	}
	
	// Makes the vertical bars
	for (int i = 1; i <= 2; i++) {
		mat[i + rowNum][0] = '|';
		mat[i + rowNum][MAT_WIDTH - 1] = '|';
	}

	return mat;
}

// Adds indicator to the board to show whose turn it is
void UserInterface :: addTurnIndicator(wchar_t board[BOARD_HEIGHT][BOARD_WIDTH], int p_index) {

	int topRow = 5;
	int botRow = 15;
	switch (p_index) {
		case 0:
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 2] = '*';
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 1] = '*';
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2] = '*';
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 + 1] = '*';
			break;
		case 1:
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 2] = '*';
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 1] = '*';
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2] = '*';
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 + 1] = '*';
			break;
		case 2:
			board[botRow][MAT_WIDTH/2 - 2] = '*';
			board[botRow][MAT_WIDTH/2 - 1] = '*';
			board[botRow][MAT_WIDTH/2] = '*';
			board[botRow][MAT_WIDTH/2 + 1] = '*';
			break;
		case 3:
			board[topRow][MAT_WIDTH/2 - 2] = '*';
			board[topRow][MAT_WIDTH/2 - 1] = '*';
			board[topRow][MAT_WIDTH/2] = '*';
			board[topRow][MAT_WIDTH/2 + 1] = '*';
			break;
		case 4:
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 2] = '*';
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 1] = '*';
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2] = '*';
			board[botRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 + 1] = '*';
			break;
		case 5:
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 2] = '*';
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 - 1] = '*';
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2] = '*';
			board[topRow][MAT_WIDTH + MAT_SPACE + MAT_WIDTH + MAT_SPACE + MAT_WIDTH/2 + 1] = '*';
			break;
	}
}
void UserInterface :: displayPlayerHand(Player *p) {

	char **phand = new char*[MAT_HEIGHT];
	for (int i = 0; i < MAT_HEIGHT; i++) {
		phand[i] = new char[MAT_WIDTH + 1];
		for (int k = 0; k < MAT_WIDTH; k++) {
			phand[i][k] = ' ';
		}
	}

	// Writes the name to the mat
	string name = p->getName() + "'s hand";
	int nameStart = (MAT_WIDTH - name.size()) / 2;
	for (int i = 0; i < (int) name.size(); i++) {
		phand[0][nameStart + i] = name.at(i);
	}

	for (int i = 0; i < MAT_WIDTH; i++) {
		if (i >= 2 && (i - 3) % 6 == 0) {
			// Writes the hand indices to the mat	 
			phand[2][i] = 'H';
			phand[2][i + 1] = (i - 3) / 6 + 1 + '0';

			// Writes the card values to the mat
			if ((i-3)/6 < p->hand.getSize()) {
				string cardNum = std::to_string((p->hand.cards.at((i - 3) / 6)).getNumber());
				if (cardNum == "13") {
					phand[3][i] = 'S';
					phand[3][i + 1] = 'B';
				} else if (cardNum.length() == 1) {
					phand[3][i] = ' ';
					phand[3][i + 1] = cardNum.at(0);
				} else {
				
					phand[3][i] = cardNum.at(0);
					phand[3][i + 1] = cardNum.at(1);
				}
			} else {
				phand[3][i] = ' ';
				phand[3][i + 1] = ' ';
			}
		}
	
		// Writes the brackets for the cards
		else if (i >= 2 && (i - 2) % 6 == 0) {
			phand[3][i] = '[';
			phand[3][i + 3] = ']';
		}	
			
		phand[1][i] = '-';
		phand[4][i] = '-';
	}

	// Makes the vertical bars
	for (int i = 2; i <= 3; i++) {
		phand[i][0] = '|';
		phand[i][MAT_WIDTH - 1] = '|';
	}


	for (int i = 0; i < MAT_HEIGHT; i++) {
		cout << std::setfill(' ') << std::setw(MAT_SPACE + MAT_WIDTH*2); 
		phand[i][MAT_WIDTH] = '\0';
		cout << phand[i] << endl;
		delete[] phand[i]; // Frees memory allocated
	}
	delete[] phand;
	
}

// Gets the row at which to place the player
int UserInterface :: getPlayerRow(int pNum) {
	if (pNum % 2 == 0) {
		return 0;
	} else {
		return MIDDLE_SPACE + MAT_HEIGHT;
	}
}

// Gets the column at which to place the player
int UserInterface :: getPlayerCol(int pNum) {
	if (pNum % 2 != 0) {
		return getPlayerCol(pNum + 1);
	} else {
		int col;
		switch (pNum) {	
			case 4:
				col = 0; break;
			case 2:
				col = MAT_WIDTH + MAT_SPACE; break;
			case 6: 
				col = (MAT_WIDTH + MAT_SPACE) * 2; break;
		}
		return col;
	}
}

void UserInterface :: promptSave(Game &g) {
	// Prompts the user to save
	cout << "Would you like to save the game (yes/no)? ";
	string input;
	cin >> input;
	while (input != "yes" && input != "no") {
		cout << "Please enter either yes or no!\n";
		cout << "Would you like to save the game (yes/no)? ";
		cin >> input;
	}

	if (input == "yes") {
		cout << "What file would you like to save to? ";
		cin >> input;
		g.save(input);
		cout << "... Save complete!\n";
	}
}

// Prints the winner to the TUI
void UserInterface :: printWinner(string &winner) {
	// Ending message
	cout << "\n\n\n";
	cout << std::setfill(' ') << std::setw(MAT_WIDTH*2 + MAT_SPACE) << "********CONGRATULATIONS!********" << endl;

	string win_msg = winner + " has won the game!";
	cout << std::setfill(' ') << std::setw(MAT_WIDTH*3/2 + MAT_SPACE + win_msg.size()/2) << win_msg <<endl;
}
