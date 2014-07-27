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
#include "../headers/System_RandomPlayer.h"
#include "../headers/System_ThePlayerWhoNeverBusts.h"
#include "../headers/System_SimplePointCount.h"
#include "../headers/System_FullPointCount.h"
#include "../headers/System_TenCount.h"
#include "../headers/Player.h"
#include "../headers/Box.h"
#include <string.h>

extern GlobalCount count;

// TMP
Box::Box()
{
	/*
	int i = 0;
	for (i = 0 ; i < 21 ; i++)
	{
		for (int j = 0 ; j < 10 ; j++)
		{
			Box::_stats[i][j] = -1;
		}
	}*/
	
	this->reset();
}

void Box::reset()
{
	this->player = NULL;
	this->bet = 0;
	this->insurance = false;
	//this->splitIndex = 0;
	this->hand.reset();
	/*for (int i = 0 ; i < MAX_SPLIT ; i++)
	{
		this->splits[i].reset();
	}*/
}

bool Box::insure()
{
	if (this->player->insure((double)((double)this->bet) / ((double)2)))
	{
		this->player->betInsurance((double)((double)this->bet) / ((double)2));
		return this->insurance = true;
	}
	return false;
}

bool Box::hasInsured()
{
	return this->insurance;
}

void Box::payInsurance()
{
	if (this->hasInsured())
	{
		this->player->win(this->bet * 1.5);
	}
}

void Box::add(int value)
{
	this->hand.add(value);
}

void Box::take(Player* player, int bet)
{
	this->take(player, bet, false);
}
void Box::take(Player* player, int bet, bool isSplitted)
{
	this->player = player;
	this->bet = bet;
	this->hand.setSplitted(isSplitted);
}

int Box::doubleDown()
{
	int bet = this->player->betAmount(this->bet);
	this->bet += bet;
	return bet;
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

int Box::getSoftValue()
{
	return this->hand.getSoftValue();
}

int Box::getBet()
{
	return this->bet;
}

Hand* Box::getHand()
{
	return &this->hand;
}
Player* Box::getPlayer()
{
	return this->player;
}


// TMP
int Box::decision(Hand* dealerHand, bool canSplit, bool canDoubleDown)
{
	if (DEBUG) count.printStatus();
	int decision = this->player->decision(&this->hand, dealerHand, canSplit && this->hand.isPair(), this->hand.getSize() == 2 && canDoubleDown);
	
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



