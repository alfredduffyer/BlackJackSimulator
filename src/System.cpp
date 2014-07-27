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

System::System()
{
	int i = 0;
	this->comparator = 0;
	this->hardStanding = (double**)calloc(8, sizeof(double[10]));
	this->softStanding = (double**)calloc(3, sizeof(double[10]));
	this->hardDoublingDown = (double**)calloc(10, sizeof(double[10]));
	this->softDoublingDown = (double**)calloc(9, sizeof(double[10]));
	this->splittingPairs = (double**)calloc(10, sizeof(double[10]));
	for (i = 0 ; i < 10 ; i++)
	{
		this->hardDoublingDown[i] = (double*)calloc(10, sizeof(double));
		this->splittingPairs[i] = (double*)calloc(10, sizeof(double));
		if (i < 9)
		{
			this->softDoublingDown[i] = (double*)calloc(10, sizeof(double));
		}
		if (i < 8)
		{
			this->hardStanding[i] = (double*)calloc(10, sizeof(double));
		}
		if (i < 3)
		{
			this->softStanding[i] = (double*)calloc(10, sizeof(double));
		}
	}
}

bool System::insure()
{
	return false;
}

int System::howManyHands(int maxHands)
{
	if (maxHands){};
	return 1;
}

bool System::split(int player, int dealer)
{
	player = (player == 1) ? 11 : player;
	//printf("[%d;%d]\n", player, dealer-1);
	return (this->comparator > this->splittingPairs[player-SHIFT_SP][dealer-1]);
}

bool System::doubleDown(int player, int dealer, bool soft)
{
	//printf("[%d;%d;%d]\n", player-SHIFT_SDD % 10, dealer-1, soft ? 1 : 0);
	if (soft)
	{
		return (this->comparator > this->softDoublingDown[(player-SHIFT_SDD) % 10][dealer-1]);
	}
	return (this->comparator > this->hardDoublingDown[player-SHIFT_HDD][dealer-1]);
}

bool System::draw(int player, int dealer, bool soft)
{
	//printf("[%d;%d;%d]\n", player, dealer-1, soft ? 1 : 0);
	if (soft)
	{
		return (this->comparator < this->softStanding[player-SHIFT_SS][dealer-1]);
	}
	return (this->comparator < this->hardStanding[player-SHIFT_HS][dealer-1]);
}

int System::exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (player && dealer && canSplit && canDoubleDown){}
	return 0;
}

int System::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	this->updateComparator();
	
	int exceptionReturn = this->exception(player, dealer, canSplit, canDoubleDown);
	
	if (exceptionReturn)
	{
		return exceptionReturn;
	}
	
	int playerSoftValue = player->getSoftValue();
	int playerValue = player->getValue();
	int dealerValue = dealer->getSoftValue();
	/*
	if (playerSoftValue == 12 && (dealerValue == 7 || dealerValue == 8 || dealerValue == 9))
	{
		printf("(%d,%d) against a %d, canSplit=(%s), isPair=(%s)\n", playerSoftValue/2, playerSoftValue/2, dealerValue, canSplit?"true":"false", player->isPair()?"true":"false");
		system("echo \"PAUSE\" && read a");
	}
	*/
	
	if (canSplit && player->isPair() && this->split(playerSoftValue/2, dealerValue))
	{
		if (DEBUG) printf("  --> Splitting a (%d,%d) against a %d\n", playerSoftValue/2, playerSoftValue/2, dealerValue);
		return SPLIT;
	}
	
	if (canDoubleDown && player->isSoft() && (playerSoftValue == 2 || (playerValue >= 13 && playerValue < 20)) && this->doubleDown(playerValue, dealerValue, true))
	{
		if (DEBUG) printf("  --> Doubling down a soft %d against a %d\n", playerValue, dealerValue);
		return DOUBLEDOWN;
	}
	
	if (canDoubleDown && !player->isSoft() && playerValue >= 2 && playerValue <= 11 && this->doubleDown(playerValue, dealerValue, false))
	{
		if (DEBUG) printf("  --> Doubling down a hard %d against a %d\n", playerValue, dealerValue);
		return DOUBLEDOWN;
	}
	
	if (player->isSoft() && playerValue >= 17 && playerValue <= 19 && this->draw(playerValue, dealerValue, true))
	{
		if (DEBUG) printf("  --> Drawing on a soft %d against a %d\n", playerValue, dealerValue);
		return DRAW;
	}
	
	if (!player->isSoft() && playerValue < 20 && (playerValue < 12 || this->draw(playerValue, dealerValue, false)))
	{
		if (DEBUG) printf("  --> Drawing on a hard %d against a %d\n", playerValue, dealerValue);
		return DRAW;
	}
	
	if (DEBUG) printf("  --> Standing on a %s %d against a %d\n", ((player->isSoft()) ? "soft" : "hard"), playerValue, dealerValue);
	return STAND;
}

int System::bet()
{
	return 1;
}

void System::updateComparator()
{
	this->comparator = 0;
}

System::~System()
{
	free(this->hardStanding);
	free(this->softStanding);
	free(this->hardDoublingDown);
	free(this->softDoublingDown);
	free(this->splittingPairs);
}


