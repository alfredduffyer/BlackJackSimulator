#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"
#include "functions.h"
#include "print.h"
#include "Card.h"
#include "GlobalCount.h"
#include "Hand.h"
#include "Shoe.h"
#include "System.h"
#include "System_BasicStrategy.h"
#include "System_Dealer.h"
#include "System_RandomPlayer.h"
#include "System_ThePlayerWhoNeverBusts.h"
#include "System_SimplePointCount.h"
#include "System_FullPointCount.h"
#include "System_TenCount.h"
#include "Player.h"

#ifndef BOX_H
#define BOX_H

class Box
{
	public:
		Player* player;			// Player who is playing on the box
		Hand hand;				// Hand dealt to the player on the box
	private:
		int bet;				// Bet placed by the player on the box
		bool insurance;			// True if the hand is insured, false otherwise
		
	
	public:
		Box();					// Calls reset()
		void reset();			// Resets the box (no player, no bet...)
		void take(Player* player, int bet);						// Takes the box by a player that places a bet
		void take(Player* player, int bet, bool isSplitted);	// Takes the box by a player who splits his pair 
		bool insure();			// true if it insures the box if the players should according to his strategy, false otherwise
		int doubleDown();		// Doubles down the box
		int decision(Hand* dealerHand, bool canSplit, bool canDoubleDown);		// Takes a decision according to the player's system with all the parameters of the situation
		void payInsurance();	// Pays the insurance to the player
		void tie();				// Gives the player his bet back
		void win();				// Gives the player his bet and his win (1 or 1.5 times his bet)
		bool isFree();			// true if the box hasn't been taken by a player (is free), false otherwise
		bool hasInsured();		// true if the hand has been insured, false otherwise
		int getBet();			// Gives the bet that was placed on the box
		
		static int _stats[21][10];			// TEMP
};

#endif
