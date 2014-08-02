#include "../headers/_variables.h"
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/GlobalCount.h"
#include "../headers/System_FullPointCount.h"

extern GlobalCount count;

System_FullPointCount::System_FullPointCount() : System()
{
	this->initiateTables();
}

bool System_FullPointCount::insure()
{
	return count.getHiLoIndex() > 8;
}

int System_FullPointCount::bet()
{
	int index = count.getHiLoIndex() / 2;
	
	if (!ACTIVATE_BET_VARIATION || MAX_BET_VARIATION <= 1 || index < 1)
	{
		return 1;
	}
	
	if (MAX_BET_VARIATION >= 3 && index >= 5)
	{
		return 3;
	}
	
	return 2;
}

int System_FullPointCount::howManyHands(int maxHands)
{
	maxHands = (maxHands <= MAX_HAND_VARIATION) ? maxHands : MAX_HAND_VARIATION;
	
	int index = count.getHiLoIndex() / 2;
	
	if (index < 0)
	{
		return 1;
	}
	if (index <= 2)
	{
		return 2;
	}
	if (index > maxHands)
	{
		return maxHands;
	}
	
	return (index * 8 + random(1, maxHands) * 2) / 10;
}

int System_FullPointCount::exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (canDoubleDown && player->isSoft() && player->getValue() == 17 && dealer->getValue() == 2 && count.getHiLoIndex() >= 1 && count.getHiLoIndex() <= 10)
	{
		return  DOUBLEDOWN;
	}
	
	if (canSplit && (player->getSoftValue() / 2) == 4 && dealer->getValue() == 6 && count.getHiLoIndex() > 5 && !canDoubleDown)
	{
		return SPLIT;
	}
	
	if (canSplit && (player->getSoftValue() / 2) == 8 && dealer->getValue() == 10 && count.getHiLoIndex() < 24)
	{
		return SPLIT;
	}
	
	if (canSplit && (player->getSoftValue() / 2) == 3 && dealer->getValue() == 8 && (count.getHiLoIndex() > 6 || count.getHiLoIndex() < -2))
	{
		return SPLIT;
	}
	
	return 0;
}

void System_FullPointCount::updateComparator()
{
	this->comparator = count.getHiLoIndex();
}

void System_FullPointCount::initiateTables()
{
	this->initiate_hardStandingNumbers();
	this->initiate_softStandingNumbers();
	this->initiate_hardDoublingDown();
	this->initiate_softDoublingDown();
	this->initiate_splittingPairs();
	
	/*
	printBlackJackTables(this->hardStanding, 8, 10, SHIFT_HS, false);
	printBlackJackTables(this->softStanding, 3, 10, SHIFT_SS, false);
	printBlackJackTables(this->hardDoublingDown, 10, 10, SHIFT_HDD, false);
	printBlackJackTables(this->softDoublingDown, 9, 10, SHIFT_SDD, false, 'A');
	printBlackJackTables(this->splittingPairs, 10, 10, SHIFT_SP, false, 'S');
	spause();
	*/
}

void System_FullPointCount::initiate_hardStandingNumbers()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->hardStanding[7][i] = -99;
		this->hardStanding[6][i] = -99;
		this->hardStanding[5][i] = -99;
	}
	
	for (i = 8 ; i <= 10 ; i++)
	{
		this->hardStanding[2][i%10] = 99;
		this->hardStanding[1][i%10] = 99;
		this->hardStanding[0][i%10] = 99;
	}
	
	this->hardStanding[0][1] = 14;
	this->hardStanding[0][2] = 6;
	this->hardStanding[0][3] = 2;
	this->hardStanding[0][4] = -1;
	this->hardStanding[0][5] = 0;
	
	this->hardStanding[1][1] = 1;
	this->hardStanding[1][2] = -2;
	this->hardStanding[1][3] = -5;
	this->hardStanding[1][4] = -9;
	this->hardStanding[1][5] = -8;
	this->hardStanding[1][6] = 50;
	
	this->hardStanding[2][1] = -5;
	this->hardStanding[2][2] = -8;
	this->hardStanding[2][3] = -13;
	this->hardStanding[2][4] = -17;
	this->hardStanding[2][5] = -17;
	this->hardStanding[2][6] = 20;
	this->hardStanding[2][7] = 38;
	
	this->hardStanding[3][1] = -12;
	this->hardStanding[3][2] = -17;
	this->hardStanding[3][3] = -21;
	this->hardStanding[3][4] = -26;
	this->hardStanding[3][5] = -28;
	this->hardStanding[3][6] = 13;
	this->hardStanding[3][7] = 15;
	this->hardStanding[3][8] = 12;
	this->hardStanding[3][9] = 8;
	this->hardStanding[3][0] = 16;
	
	this->hardStanding[4][1] = -21;
	this->hardStanding[4][2] = -25;
	this->hardStanding[4][3] = -30;
	this->hardStanding[4][4] = -34;
	this->hardStanding[4][5] = -35;
	this->hardStanding[4][6] = 10;
	this->hardStanding[4][7] = 11;
	this->hardStanding[4][8] = 6;
	this->hardStanding[4][9] = 0;
	this->hardStanding[4][0] = 14;
	
	this->hardStanding[5][0] = -15;
	this->hardStanding[0][6] = 99;
	this->hardStanding[0][7] = 99;
	this->hardStanding[1][7] = 99;
}

void System_FullPointCount::initiate_softStandingNumbers()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->softStanding[0][i] = 99;
		this->softStanding[1][i] = -99;
		this->softStanding[2][i] = -99;
	}
	
	this->softStanding[0][6] = 29;
	this->softStanding[1][8] = 99;
	this->softStanding[1][9] = 12;
	this->softStanding[1][0] = -6;
}

void System_FullPointCount::initiate_hardDoublingDown()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->hardDoublingDown[0][i] = 99;
		this->hardDoublingDown[1][i] = 99;
		this->hardDoublingDown[2][i] = 99;
		this->hardDoublingDown[3][i] = 99;
		this->hardDoublingDown[4][i] = 99;
		this->hardDoublingDown[5][i] = 99;
		this->hardDoublingDown[6][i] = 99;
		this->hardDoublingDown[7][i] = 99;
	}
	
	this->hardDoublingDown[3][4] = 20;
	this->hardDoublingDown[3][5] = 26;
	
	this->hardDoublingDown[4][3] = 27;
	this->hardDoublingDown[4][4] = 18;
	this->hardDoublingDown[4][5] = 24;
	
	this->hardDoublingDown[5][2] = 45;
	this->hardDoublingDown[5][3] = 21;
	this->hardDoublingDown[5][4] = 14;
	this->hardDoublingDown[5][5] = 17;
	
	this->hardDoublingDown[6][2] = 22;
	this->hardDoublingDown[6][3] = 11;
	this->hardDoublingDown[6][4] = 05;
	this->hardDoublingDown[6][5] = 05;
	this->hardDoublingDown[6][6] = 22;
	
	this->hardDoublingDown[7][1] = 03;
	this->hardDoublingDown[7][2] = 0;
	this->hardDoublingDown[7][3] = -5;
	this->hardDoublingDown[7][4] = -10;
	this->hardDoublingDown[7][5] = -12;
	this->hardDoublingDown[7][6] = 4;
	this->hardDoublingDown[7][7] = 14;
	
	this->hardDoublingDown[8][1] = -15;
	this->hardDoublingDown[8][2] = -17;
	this->hardDoublingDown[8][3] = -21;
	this->hardDoublingDown[8][4] = -24;
	this->hardDoublingDown[8][5] = 26;
	this->hardDoublingDown[8][6] = -17;
	this->hardDoublingDown[8][7] = -9;
	this->hardDoublingDown[8][8] = -3;
	this->hardDoublingDown[8][9] = 7;
	this->hardDoublingDown[8][0] = 6;
	
	this->hardDoublingDown[9][1] = -23;
	this->hardDoublingDown[9][2] = -26;
	this->hardDoublingDown[9][3] = -29;
	this->hardDoublingDown[9][4] = -33;
	this->hardDoublingDown[9][5] = -35;
	this->hardDoublingDown[9][6] = -26;
	this->hardDoublingDown[9][7] = -16;
	this->hardDoublingDown[9][8] = -10;
	this->hardDoublingDown[9][9] = -9;
	this->hardDoublingDown[9][0] = -3;
}

void System_FullPointCount::initiate_softDoublingDown()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->softDoublingDown[0][i] = 99;
	}
	
	for (i = 0 ; i <= 8 ; i++)
	{
		this->softDoublingDown[i][1] = 99;
		this->softDoublingDown[i][6] = 99;
		this->softDoublingDown[i][7] = 99;
		this->softDoublingDown[i][8] = 99;
		this->softDoublingDown[i][9] = 99;
		this->softDoublingDown[i][0] = 99;
	}
	
	this->softDoublingDown[1][2] = 10;
	this->softDoublingDown[1][3] = 2;
	this->softDoublingDown[1][4] = -19;
	this->softDoublingDown[1][5] = -13;
	
	this->softDoublingDown[2][2] = 11;
	this->softDoublingDown[2][3] = -3;
	this->softDoublingDown[2][4] = -13;
	this->softDoublingDown[2][5] = -19;
	
	this->softDoublingDown[3][2] = 19;
	this->softDoublingDown[3][3] = -7;
	this->softDoublingDown[3][4] = -16;
	this->softDoublingDown[3][5] = -23;
	
	this->softDoublingDown[4][2] = 21;
	this->softDoublingDown[4][3] = -6;
	this->softDoublingDown[4][4] = -16;
	this->softDoublingDown[4][5] = -32;
	
	this->softDoublingDown[5][2] = -6;
	this->softDoublingDown[5][3] = -14;
	this->softDoublingDown[5][4] = -28;
	this->softDoublingDown[5][5] = -30;
	
	this->softDoublingDown[6][2] = -2;
	this->softDoublingDown[6][3] = -15;
	this->softDoublingDown[6][4] = -18;
	this->softDoublingDown[6][5] = -23;
	
	this->softDoublingDown[7][2] = -9;
	this->softDoublingDown[7][3] = -5;
	this->softDoublingDown[7][4] = -1;
	this->softDoublingDown[7][5] = 0;
	
	this->softDoublingDown[8][2] = 20;
	this->softDoublingDown[8][3] = 12;
	this->softDoublingDown[8][4] = 8;
	this->softDoublingDown[8][5] = 8;
}

void System_FullPointCount::initiate_splittingPairs()
{
	int i = 0;
	
	for (i = 1 ; i <= 10 ; i++)
	{
		this->splittingPairs[3][i%10] = 99;
		if (i >= 5 && i <= 10)
		{
			this->splittingPairs[2][i%10] = 99;
		}
		if (i >= 7 && i <= 10)
		{
			this->splittingPairs[4][i%10] = 99;
			this->splittingPairs[1][i%10] = 99;
			this->splittingPairs[0][i%10] = 99;
		}
		if (i >= 4 && i <= 7)
		{
			this->splittingPairs[5][i%10] = -99;
		}
		if (i >= 1 && i <= 8)
		{
			this->splittingPairs[6][i%10] = -99;
		}
		if (i >= 7 && i <= 10)
		{
			this->splittingPairs[8][i%10] = 99;
		}
		if (i >= 1 && i <= 5)
		{
			this->splittingPairs[9][i%10] = -99;
		}
	}
	
	this->splittingPairs[0][1] = -9;
	this->splittingPairs[0][2] = 15;
	this->splittingPairs[0][3] = -22;
	this->splittingPairs[0][4] = -30;
	this->splittingPairs[0][5] = -99;
	this->splittingPairs[0][6] = -99;
	
	this->splittingPairs[1][1] = -21;
	this->splittingPairs[1][2] = -34;
	this->splittingPairs[1][3] = -99;
	this->splittingPairs[1][4] = -99;
	this->splittingPairs[1][5] = -99;
	this->splittingPairs[1][6] = -99;
	
	this->splittingPairs[2][1] = 99;
	this->splittingPairs[2][2] = 18;
	this->splittingPairs[2][3] = 8;
	this->splittingPairs[2][4] = 0;
	
	this->splittingPairs[4][1] = 0;
	this->splittingPairs[4][2] = -3;
	this->splittingPairs[4][3] = -8;
	this->splittingPairs[4][4] = -13;
	this->splittingPairs[4][5] = -16;
	this->splittingPairs[4][6] = -8;
	
	this->splittingPairs[5][1] = -22;
	this->splittingPairs[5][2] = -29;
	this->splittingPairs[5][3] = -35;
	this->splittingPairs[5][8] = 99;
	this->splittingPairs[5][9] = 99;
	this->splittingPairs[5][0] = 99;
	
	this->splittingPairs[6][9] = 99;
	this->splittingPairs[6][0] = -18;
	
	this->splittingPairs[7][1] = -3;
	this->splittingPairs[7][2] = -8;
	this->splittingPairs[7][3] = -10;
	this->splittingPairs[7][4] = -15;
	this->splittingPairs[7][5] = -14;
	this->splittingPairs[7][6] = 8;
	this->splittingPairs[7][7] = -16;
	this->splittingPairs[7][8] = -22;
	this->splittingPairs[7][9] = 99;
	this->splittingPairs[7][0] = 10;
	
	this->splittingPairs[8][1] = 25;
	this->splittingPairs[8][2] = 17;
	this->splittingPairs[8][3] = 10;
	this->splittingPairs[8][4] = 6;
	this->splittingPairs[8][5] = 7;
	this->splittingPairs[8][6] = 19;
	
	this->splittingPairs[9][6] = -33;
	this->splittingPairs[9][7] = -24;
	this->splittingPairs[9][8] = -22;
	this->splittingPairs[9][9] = -20;
	this->splittingPairs[9][0] = -17;
}


