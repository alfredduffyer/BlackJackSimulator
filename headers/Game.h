#include "Shoe.h"
#include "Player.h"
#include "Box.h"

#ifndef GAME_H
#define GAME_H

class Game
{
	private:
		int min;			// Minimum bet at the table
		int max;			// Maximum bet at the table
		Player* dealer;			// Dealer
		Box* dealerBox;			// Dealer's box
		int nbBoxes;			// Number of boxes that can be played on
		Box* boxes;			// Boxes on the table
		Player** players;		// Players sitted at the table
		int nbPlayers;			// Number of players sitted at the table
		int* splitIndexes;		// Number of splits for each box
		Shoe* shoe;			// Table's shoe
	
	public:
		Game(Shoe* shoe);					// Calls init(min = 5, max = 500, nbBoxes = 7)
		Game(Shoe* shoe, int min, int max);			// Calls init(nbBoxes = 7)
		Game(Shoe* shoe, int min, int max, int nbBoxes);	// Calls init()
		void init(Shoe* shoe, int min, int max, int nbBoxes);	// Creates a game with all the given parameters
		int addPlayer(Player* player);				// Adds a player to the table
		void resetBoxes();					// Resets all the boxes, including the dealer's
		void initTurn();					// Initiates the turn
		int howManyHands(bool isMainPlayer, Player* player);	// Calculates the number of hands that will be played by a player
		void bet();						// Makes the players bet on the available boxes
		void deal(int boxIndex);				// Deals a card to a given box
		void deal();						// Deals the first wave (two cards on each box, one to the dealer)
		void insurance();					// Asks the player to insure their hands or not
		void decision(int boxIndex);				// Takes a decision for a given box
		void decisions();					// Deals the second wave according to players' decisions
		void payInsurance();					// Pays the insurance in the case of a Black Jack
		void pay();						// Pays the players
		int play();						// Main procedure : plays the game of Black Jack using the other methods
};

#endif
