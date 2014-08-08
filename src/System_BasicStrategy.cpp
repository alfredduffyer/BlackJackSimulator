#include "../headers/_variables.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/GlobalCount.h"
#include "../headers/System_BasicStrategy.h"
#include "../headers/Stats.h"

extern GlobalCount count;
extern Stats stats;

System_BasicStrategy::System_BasicStrategy() : System()
{
	this->initiateTables();
	this->initiateStatsException();
}

int System_BasicStrategy::howManyHands(int maxHands)
{
	if (maxHands){}
	return random(3, 7);
}

bool System_BasicStrategy::insure()
{
	return false;
}

int System_BasicStrategy::exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (canSplit && canDoubleDown){}
	return (!player->isSoft() && dealer->getValue() == 10 && player->getValue() == 16 && player->getSize() > 2) ? STAND : 0;
}

void System_BasicStrategy::initiateTables()
{
	System::initiateTables();
	this->initiate_hardStandingNumbers();
	this->initiate_softStandingNumbers();
	this->initiate_hardDoublingDown();
	this->initiate_softDoublingDown();
	this->initiate_splittingPairs();
	/*
	printBlackJackTables(this->hardStanding, 8, 10, SHIFT_HS, true);
	printBlackJackTables(this->softStanding, 3, 10, SHIFT_SS, true);
	printBlackJackTables(this->hardDoublingDown, 10, 10, SHIFT_HDD, true);
	printBlackJackTables(this->softDoublingDown, 9, 10, SHIFT_SDD, true, 'A');
	printBlackJackTables(this->splittingPairs, 10, 10, SHIFT_SP, true, 'S');
	spause();
	*/
}

void System_BasicStrategy::initiateStatsException()
{
	int playerValue = (stats.getPlayerValue() == 12) ? 11 : stats.getPlayerValue()/2;
	int dealerValue = (stats.getDealerValue() == 11) ? 0 : stats.getDealerValue() - 1;
	switch (stats.getDecisionConcerned())
	{
		case SPLIT:
			this->splittingPairs[playerValue-SHIFT_SDD][dealerValue] = stats.getDecision();
			break;
		
		case DOUBLEDOWN:
			if (stats.isSoftHand())
			{
				this->softDoublingDown[stats.getPlayerValue()-10-SHIFT_SDD][dealerValue] = stats.getDecision();
			}
			else
			{
				this->hardDoublingDown[stats.getPlayerValue()-SHIFT_HDD][dealerValue] = stats.getDecision();
			}
			break;
		
		case DRAW:
			if (stats.isSoftHand())
			{
				this->softStanding[stats.getPlayerValue()-SHIFT_SS][dealerValue] = stats.getDecision();
			}
			else
			{
				this->hardStanding[stats.getPlayerValue()-SHIFT_HS][dealerValue] = stats.getDecision();
			}
			break;
	}
	/*
	printBlackJackTables(this->hardStanding, 8, 10, SHIFT_HS, true);
	printBlackJackTables(this->softStanding, 3, 10, SHIFT_SS, true);
	printBlackJackTables(this->hardDoublingDown, 10, 10, SHIFT_HDD, true);
	printBlackJackTables(this->softDoublingDown, 9, 10, SHIFT_SDD, true, 'A');
	printBlackJackTables(this->splittingPairs, 10, 10, SHIFT_SP, true, 'S');
	*/
}

void System_BasicStrategy::initiate_hardStandingNumbers()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->hardStanding[7][i] = -1;
		this->hardStanding[6][i] = -1;
		this->hardStanding[5][i] = -1;
	}
	
	for (i = 1 ; i <= 5 ; i++)
	{
		this->hardStanding[4][i] = -1;
		this->hardStanding[3][i] = -1;
		this->hardStanding[2][i] = -1;
		this->hardStanding[1][i] = -1;
		if (i >= 3)
		{
			this->hardStanding[0][i] = -1;
		}
	}
	
	for (i = 6 ; i <= 9 ; i++)
	{
		this->hardStanding[4][i] = 1;
		this->hardStanding[3][i] = 1;
		this->hardStanding[2][i] = 1;
		this->hardStanding[1][i] = 1;
		this->hardStanding[0][i] = 1;
	}
	
	this->hardStanding[4][0] = 1;
	this->hardStanding[3][0] = 1;
	this->hardStanding[2][0] = 1;
	this->hardStanding[1][0] = 1;
	this->hardStanding[0][0] = 1;
	this->hardStanding[0][1] = 1;
	this->hardStanding[0][2] = 1;
}

void System_BasicStrategy::initiate_softStandingNumbers()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->softStanding[0][i] = 1;
		this->softStanding[1][i] = -1;
		this->softStanding[2][i] = -1;
	}
	
	this->softStanding[1][8] = 1;
	this->softStanding[1][9] = 1;
}

void System_BasicStrategy::initiate_hardDoublingDown()
{
	int i = 0, j = 0;
	
	for (i = 0 ; i <= 8 ; i++)
	{
		for (j = 0 ; j < 10 ; j++)
		{
			this->hardDoublingDown[i][j] = 1;
		}
	}
	
	for (i = 1 ; i < 10 ; i++)
	{
		this->hardDoublingDown[9][i] = -1;
		if (i < 9)
		{
			this->hardDoublingDown[8][i] = -1;
		}
		if (i < 6)
		{
			this->hardDoublingDown[7][i] = -1;
		}
	}
	
	this->hardDoublingDown[6][4] = -1;
	this->hardDoublingDown[6][5] = -1;
	
	// Changes
	this->hardDoublingDown[9][0] = 1;
}

void System_BasicStrategy::initiate_softDoublingDown()
{
	int i = 0, j = 0;
	
	for (i = 6 ; i <= 10 ; i++)
	{
		for (j = 0 ; j <= 8 ; j++)
		{
			this->softDoublingDown[j][i%10] = 1;
		}
	}
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->softDoublingDown[7][i%10] = 1;
		this->softDoublingDown[8][i%10] = 1;
	}
	
	for (i = 0 ; i <= 8 ; i++)
	{
		this->softDoublingDown[i][1] = 1;
		this->softDoublingDown[i][2] = 1;
	}
	
	for (i = 0 ; i <= 6 ; i++)
	{
		this->softDoublingDown[i][3] = -1;
		this->softDoublingDown[i][4] = -1;
		this->softDoublingDown[i][5] = -1;
	}
	
	this->softDoublingDown[0][3] = 1;
	
	this->softDoublingDown[5][1] = -1;
	this->softDoublingDown[5][2] = -1;
	this->softDoublingDown[6][2] = -1;
}

void System_BasicStrategy::initiate_splittingPairs()
{
	int i = 0, j = 0;
	
	for (i = 1 ; i <= 10 ; i++)
	{
		this->splittingPairs[8][i%10] = 1;
		this->splittingPairs[3][i%10] = 1;
		this->splittingPairs[2][i%10] = 1;
	}
	
	for (i = 7 ; i <= 10 ; i++)
	{
		for (j = 0 ; j <= 5 ; j++)
		{
			this->splittingPairs[j][i%10] = 1;
		}
	}
	
	for (i = 1 ; i <= 10 ; i++)
	{
		this->splittingPairs[9][i%10] = -1;
		this->splittingPairs[6][i%10] = -1;
		if (i <= 8)
		{
			this->splittingPairs[7][i%10] = -1;
		}
		if (i <= 7)
		{
			this->splittingPairs[5][i%10] = -1;
		}
		if (i <= 6)
		{
			this->splittingPairs[4][i%10] = -1;
			this->splittingPairs[1][i%10] = -1;
			this->splittingPairs[0][i%10] = -1;
		}
		
		this->splittingPairs[2][4] = -1;
		this->splittingPairs[7][6] = 1;
		this->splittingPairs[7][9] = 1;
		this->splittingPairs[7][0] = 1;
		
		// Changes
		this->splittingPairs[6][0] = 1;
		this->splittingPairs[9][0] = 1;
	}
}
