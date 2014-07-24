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
#include "Player.h"

#ifndef BOX_H
#define BOX_H

class Box
{
	private:
		Player* player;
		Hand hand;
		int bet;
	
	public:
		Box();
		void take(Player* player, int bet);
		void reset();
		bool isFree();
		bool isBusted();
		bool isNatural();
		char* getName();
		void add(int value);
		int getValue();
		Hand* getHand();
		int decision(Hand* dealerHand, bool canSplit, bool canDoubleDown);
		int getBet();
		void tie();
		void win();
};

#endif
