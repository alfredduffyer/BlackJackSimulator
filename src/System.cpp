#include <stdio.h>
#include <stdlib.h>
#include "../headers/_variables.h"
#include "../headers/print.h"
#include "../headers/System.h"

extern bool FORCEDEBUG;

System::System()
{
	this->updateComparator();
}

System::~System()
{
	free(this->hardStanding);
	free(this->softStanding);
	free(this->hardDoublingDown);
	free(this->softDoublingDown);
	free(this->splittingPairs);
}

void System::initiateTables()
{
	int i = 0;
	this->hardStanding = (double**)calloc(8, sizeof(double[10]));
	this->softStanding = (double**)calloc(3, sizeof(double[10]));
	this->hardDoublingDown = (double**)calloc(10, sizeof(double[10]));
	this->softDoublingDown = (double**)calloc(9, sizeof(double[10]));
	this->splittingPairs = (double**)calloc(10, sizeof(double[10]));
	for (i = 0 ; i < 10 ; i++)
	{
		this->hardDoublingDown[i] = (double*)calloc(10, sizeof(double));
		this->splittingPairs[i] = (double*)calloc(10, sizeof(double));
		if (i < 9) {
			this->softDoublingDown[i] = (double*)calloc(10, sizeof(double));
		}
		if (i < 8) {
			this->hardStanding[i] = (double*)calloc(10, sizeof(double));
		}
		if (i < 3) {
			this->softStanding[i] = (double*)calloc(10, sizeof(double));
		}
	}
}

void System::initiateStatsException()
{
	
}

void System::updateComparator()
{
	this->comparator = 0;
}

int System::howManyHands(int maxHands)
{
	if (maxHands){};
	return 1;
}

int System::bet()
{
	return 1;
}

bool System::insure()
{
	return false;
}

int System::exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (player && dealer && canSplit && canDoubleDown){}
	return 0;
}

bool System::split(int player, int dealer)
{
	player = (player == 1) ? 11 : player;
	return (this->comparator > this->splittingPairs[player-SHIFT_SP][dealer-1]);
}

bool System::doubleDown(int player, int dealer, bool soft)
{
	if (soft) {
		return (this->comparator > this->softDoublingDown[(player-SHIFT_SDD) % 10][dealer-1]);
	}
	return (this->comparator > this->hardDoublingDown[player-SHIFT_HDD][dealer-1]);
}

bool System::draw(int player, int dealer, bool soft)
{
	if (soft) {
		return (this->comparator <= this->softStanding[player-SHIFT_SS][dealer-1]);
	}
	return (this->comparator <= this->hardStanding[player-SHIFT_HS][dealer-1]);
}

int System::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	this->updateComparator();
	
	if (int exceptionReturn = this->exception(player, dealer, canSplit, canDoubleDown)) {
		return exceptionReturn;
	}
	
	int playerSoftValue = player->getSoftValue();
	int playerValue = player->getValue();
	int dealerValue = dealer->getSoftValue();
	char message[100];
	
	if (canSplit && player->isPair() && this->split(playerSoftValue/2, dealerValue))
	{
		sprintf(message, "  --> Splitting a (%d,%d) against a %d\n", playerSoftValue/2, playerSoftValue/2, dealerValue);
		debug(message, 0);
		return SPLIT;
	}
	
	if (canDoubleDown && player->isSoft() && (playerSoftValue == 2 || (playerValue >= 13 && playerValue < 20)) && this->doubleDown(playerValue, dealerValue, true))
	{
		sprintf(message, "  --> Doubling down a soft %d against a %d\n", playerValue, dealerValue);
		debug(message, 0);
		return DOUBLEDOWN;
	}
	
	if (canDoubleDown && !player->isSoft() && playerValue >= 2 && playerValue <= 11 && this->doubleDown(playerValue, dealerValue, false))
	{
		sprintf(message, "  --> Doubling down a hard %d against a %d\n", playerValue, dealerValue);
		debug(message, 0);
		return DOUBLEDOWN;
	}
	
	if (player->isSoft() && (playerValue < 17 || (playerValue >= 17 && playerValue <= 19 && this->draw(playerValue, dealerValue, true))))
	{
		sprintf(message, "  --> Drawing on a soft %d against a %d\n", playerValue, dealerValue);
		debug(message, 0);
		return DRAW;
	}
	
	if (!player->isSoft() && playerValue < 20 && (playerValue < 12 || this->draw(playerValue, dealerValue, false)))
	{
		sprintf(message, "  --> Drawing on a hard %d against a %d\n", playerValue, dealerValue);
		debug(message, 0);
		return DRAW;
	}
	
	sprintf(message, "  --> Standing on a %s %d against a %d\n", ((player->isSoft()) ? "soft" : "hard"), playerValue, dealerValue);
	debug(message, 0);
	return STAND;
}
