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
		//Hand splits[MAX_SPLIT];
		int bet;
		bool insurance;
		//int splitIndex;
	
	public:
		Box();
		void take(Player* player, int bet);
		void take(Player* player, int bet, bool isSplitted);
		void reset();
		bool isFree();
		bool isBusted();
		bool isNatural();
		char* getName();
		void add(int value);
		int getValue();
		int getSoftValue();
		Hand* getHand();
		Player* getPlayer();
		int decision(Hand* dealerHand, bool canSplit, bool canDoubleDown);
		int getBet();
		void tie();
		void win();
		double getStack();
		static int _stats[21][10];
		int doubleDown();
		void payInsurance();
		bool hasInsured();
		bool insure();
		//bool isSplit();
		//void split(int handIndex);
};

#endif