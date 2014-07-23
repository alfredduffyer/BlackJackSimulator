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
#include "Box.h"

#ifndef GAME_H
#define GAME_H

class Game
{
	private:
		int min;
		int max;
		int nbBoxes;
		Shoe* shoe;
		Player** players;         
		Box* boxes;
		int nbPlayers;
		Card* card;
		Player* dealer;
		Box* dealerBox;
	
	public:
		Game(Shoe* shoe);
		Game(Shoe* shoe, int min, int max);
		Game(Shoe* shoe, int min, int max, int nbBoxes);
		void init(Shoe* shoe, int min, int max, int nbBoxes);
		int addPlayer(Player* player);
		int removePlayer();
		void resetBoxes();
		void initShoe();
		void initTurn();
		int howManyHands(bool counter);
		void bet();
		void deal();
		Box deal(int boxIndex);
		void decisions();
		void decision(Box box, int boxIndex);
		void pay();
		void play();
		~Game();
};

#endif
