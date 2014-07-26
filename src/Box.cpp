#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/Card.h"
#include "../headers/GlobalCount.h"
#include "../headers/Hand.h"
#include "../headers/Shoe.h"
#include "../headers/System.h"
#include "../headers/System_BasicStrategy.h"
#include "../headers/System_Dealer.h"
#include "../headers/Player.h"
#include "../headers/Box.h"
#include <string.h>

// TMP
Box::Box()
{
	for (int i = 0 ; i < 21 ; i++)
	{
		for (int j = 0 ; j < 10 ; j++)
		{
			Box::_stats[i][j] = -1;
		}
	}
	
	this->reset();
}

void Box::reset()
{
	this->player = NULL;
	this->bet = 0;
	this->hand.reset();
}

void Box::add(int value)
{
	this->hand.add(value);
}

void Box::take(Player* player, int bet)
{
	this->player = player;
	this->bet = bet;
}

bool Box::isFree()
{
	return (this->bet == 0 || this->player == NULL);
}

bool Box::isBusted()
{
	return this->hand.getValue() > 21;
}

char* Box::getName()
{
	return this->player->getName();
}

double Box::getStack()
{
	return this->player->getStack();
}

void Box::tie()
{
	this->player->win(this->bet);
}

void Box::win()
{
	this->player->win(this->bet * ( (this->isNatural()) ? 2.5 : 2 ));
}

bool Box::isNatural()
{
	return this->hand.isNatural();
}

int Box::getValue()
{
	return this->hand.getValue();
}

int Box::getBet()
{
	return this->bet;
}

Hand* Box::getHand()
{
	return &this->hand;
}


// TMP
int Box::decision(Hand* dealerHand, bool canSplit, bool canDoubleDown)
{
	int decision = this->player->decision(&this->hand, dealerHand, this->hand.isPair() && canSplit, this->hand.getSize() == 2 && canDoubleDown);
	
	if (false && strcmp(this->player->getName(), "Dealer") != 0 && this->hand.isPair())
	{
		system("clear");
		int x = dealerHand->getSoftValue();
		int y = this->hand.getSoftValue();
		char error[100];
		bool isError = false;
		
		if (decision == SPLIT)
		{
			isError = (Box::_stats[y-1][x-1] != -1 && Box::_stats[y-1][x-1] != 1);
			sprintf(error, "Error found : stats[%d][%d] = %d, tried to change it to 1\n", y/2, x, Box::_stats[y-1][x-1]);
			Box::_stats[y-1][x-1] = 1;
		}
		else
		{
			isError = (Box::_stats[y-1][x-1] != -1 && Box::_stats[y-1][x-1] != 0);
			sprintf(error, "Error found : stats[%d][%d] = %d, tried to change it to 0\n", y/2, x, Box::_stats[y-1][x-1]);
			Box::_stats[y-1][x-1] = 0;
		}
		
		printStatTable(Box::_stats, true);
		
		if (isError)
		{
			puts("\n\n\n\n\n\n");
			printColor(C_RED, error);
			addToFile((char*) "statserror.txt", error);
			system("echo \"PAUSE\" && read a");
			//sleep(10);
		}
	}
	
	return decision;
}



