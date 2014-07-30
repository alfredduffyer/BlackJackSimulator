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

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		char* name;			// Player's name
		double stack;		// Player's money, in any currency
		int unit;			// Minimum bet (used when the shoe is cold, or when not counting cards)
		System* system;		// Player's strategy
	
	public:
		Player(char* name, double stack, int unit, System* system);
		int bet(int bet);							// Bets a certain amount of units according to the player's strategy
		int bet();									// Bets the amount of units given in parameter
		int betAmount(int bet);						// Bets an amount of money, that will be transformed into a number of units
		void betInsurance(double amount);			// Bets the maximum amount the insurance provides (half of the bet)
		char* getName();							// Gives the player's name
		double getStack();							// Gives the player's stack
		int getUnit();								// Gives the player's minimum bet
		int howManyHands(int maxHands);				// Gives how many hands the player wants to play
		bool insure(double amount);					// true if the player should insure according to his strategy, false otherwise
		void win(double amount);					// Updates the stack with an amount of money won
		int decision(Hand* playerHand, Hand* dealerHand, bool canSplit, bool canDoubleDown);		// Takes a decision according to the player's system with all the parameters of the situation
};

#endif
