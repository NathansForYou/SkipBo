#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <string>
#include <fstream>
#include "Card.h"
#include "Move.h"
#include "Pile.h"
#include "Hand.h"
#include "Game.h"

#define DISCARD_NUM 4
#define INVALID_ERROR "invalid"

class UserInterface;
class PersonTest;
class Player {
	private:
		friend class UserInterface;
		friend class PersonTest;
		std::string name; // The player's name
		Pile stack; // The player's main stack of cards
		std::vector<Pile> discardPiles; // The player's set of discard piles
		Hand hand; // The player's hand
	
	protected:
		Game *game; // Current instance of the game	
		// Plays the requested move, returning true if possible
		// and false if invalid
		bool play(const Move &);

	public:
		Player(std::string n = ""); // Constructor that takes name
		// Constructor that takes all information about a player (for loading)
		Player(std::string n, const Pile &s, std::vector<Pile> d, Hand h);
		virtual ~Player(); // Virtual destructor so we can clean up

		// Gets the number of cards in the player's hand
		int getHandSize() const;

		// Returns the player's name
		std::string getName() const;
	
		// Gets the number of cards in the player's stack
		int getStackSize() const;

		// Adds card(s) to the hand from the deck, 
		// returning previous number of cards in hand
		void addToHand(const Card); // Adds a card to the player's hand
		int addToHand(const std::vector<Card> &);

		// Returns true if human, false if other
		virtual bool isHuman() const = 0;

		void setGame(Game *); // Sets the game instance

		void addToStack(Card);

		void dispMove(Move) const;

		virtual bool move() = 0; 

		// Saves all player data to file
		std::string savePlayer() const;

		// Loads the player from a file
		void loadPlayer(std::istream &);
		
};

#endif
