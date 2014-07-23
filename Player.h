#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		double stack;
		int unit;
		System* system;
	
	public:
		Player(double stack, int unit, System* system);
		int bet();
		int bet(int bet);
		void win(double amount);
		int getUnit();
		int decision(Hand* playerHand, Hand* dealerHand, bool canSplit, bool canDoubleDown);
		~Player();
};

#endif
