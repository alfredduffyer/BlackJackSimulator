#include "../headers/_variables.h"
#include "../headers/_config.h"
#include "../headers/GlobalCount.h"
#include "../headers/System_TenCount.h"

extern GlobalCount count;

System_TenCount::System_TenCount() : System()
{
	this->initiateTables();
}

bool System_TenCount::insure()
{
	return count.getTenCount() < 2;
}

int System_TenCount::bet()
{
	double index = count.getTenCount();
	
	if (!ACTIVATE_BET_VARIATION || MAX_BET_VARIATION <= 1 || index > 2)
	{
		return 1;
	}
	
	if (MAX_BET_VARIATION >= 3 && index <= 1.65)
	{
		return 3;
	}
	
	return 2;
}

int System_TenCount::howManyHands(int maxHands)
{
	maxHands = (maxHands <= MAX_HAND_VARIATION) ? maxHands : MAX_HAND_VARIATION;
	
	double index = count.getTenCount();
	
	if (index <= 2.25 && index > 1.95)
	{
		return 2 > maxHands ? maxHands : 2;
	}
	if (index <= 1.95 && index > 1.75)
	{
		return 3 > maxHands ? maxHands : 3;
	}
	if (index <= 1.75 && index > 1.65)
	{
		return 4 > maxHands ? maxHands : 4;
	}
	if (index <= 1.65 && index > 1.60)
	{
		return 5 > maxHands ? maxHands : 5;
	}
	if (index <= 1.60 && index > 1.55)
	{
		return 6 > maxHands ? maxHands : 6;
	}
	if (index <= 1.55)
	{
		return 7 > maxHands ? maxHands : 7;
	}
	
	return 1;
}

int System_TenCount::exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (player && dealer && canSplit && canDoubleDown){}
	return 0;
}

void System_TenCount::updateComparator()
{
	this->comparator = count.getTenCount();
}

bool System_TenCount::split(int player, int dealer)
{
	player = (player == 1) ? 11 : player;
	//printf("[%d;%d]\n", player, dealer-1);
	return (this->comparator <= this->splittingPairs[player-SHIFT_SP][dealer-1]);
}

bool System_TenCount::doubleDown(int player, int dealer, bool soft)
{
	//printf("[%d;%d;%d]\n", player-SHIFT_SDD % 10, dealer-1, soft ? 1 : 0);
	if (soft)
	{
		return (this->comparator <= this->softDoublingDown[(player-SHIFT_SDD) % 10][dealer-1]);
	}
	return (this->comparator <= this->hardDoublingDown[player-SHIFT_HDD][dealer-1]);
}

bool System_TenCount::draw(int player, int dealer, bool soft)
{
	//printf("[%d;%d;%d]\n", player, dealer-1, soft ? 1 : 0);
	if (soft)
	{
		return (this->comparator > this->softStanding[player-SHIFT_SS][dealer-1]);
	}
	return (this->comparator > this->hardStanding[player-SHIFT_HS][dealer-1]);
}

void System_TenCount::initiateTables()
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

void System_TenCount::initiate_hardStandingNumbers()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->hardStanding[7][i] = 9;
		this->hardStanding[6][i] = 9;
		this->hardStanding[5][i] = 9;
	}
	
	this->hardStanding[5][0] = 3.1;
	
	this->hardStanding[0][1] = 2.0;
	this->hardStanding[0][2] = 2.1;
	this->hardStanding[0][3] = 2.2;
	this->hardStanding[0][4] = 2.4;
	this->hardStanding[0][5] = 2.3;
	this->hardStanding[0][6] = -0.1;
	this->hardStanding[0][7] = -0.1;
	this->hardStanding[0][8] = -0.1;
	this->hardStanding[0][9] = 1.1;
	this->hardStanding[0][0] = 1.0;
	
	this->hardStanding[1][1] = 2.3;
	this->hardStanding[1][2] = 2.5;
	this->hardStanding[1][3] = 2.6;
	this->hardStanding[1][4] = 3.0;
	this->hardStanding[1][5] = 2.7;
	this->hardStanding[1][6] = -0.1;
	this->hardStanding[1][7] = -0.1;
	this->hardStanding[1][8] = -0.1;
	this->hardStanding[1][9] = 1.3;
	this->hardStanding[1][0] = 1.1;
	
	this->hardStanding[2][1] = 2.7;
	this->hardStanding[2][2] = 2.9;
	this->hardStanding[2][3] = 3.3;
	this->hardStanding[2][4] = 3.7;
	this->hardStanding[2][5] = 3.4;
	this->hardStanding[2][6] = -0.1;
	this->hardStanding[2][7] = -0.1;
	this->hardStanding[2][8] = 1.1;
	this->hardStanding[2][9] = 1.6;
	this->hardStanding[2][0] = 1.2;
	
	this->hardStanding[3][1] = 3.2;
	this->hardStanding[3][2] = 3.6;
	this->hardStanding[3][3] = 4.1;
	this->hardStanding[3][4] = 4.8;
	this->hardStanding[3][5] = 4.3;
	this->hardStanding[3][6] = -0.1;
	this->hardStanding[3][7] = -0.1;
	this->hardStanding[3][8] = 1.4;
	this->hardStanding[3][9] = 1.9;
	this->hardStanding[3][0] = 1.3;
	
	this->hardStanding[4][1] = 3.9;
	this->hardStanding[4][2] = 4.5;
	this->hardStanding[4][3] = 5.3;
	this->hardStanding[4][4] = 6.5;
	this->hardStanding[4][5] = 4.6;
	this->hardStanding[4][6] = -0.1;
	this->hardStanding[4][7] = 1.2;
	this->hardStanding[4][8] = 1.7;
	this->hardStanding[4][9] = 2.2;
	this->hardStanding[4][0] = 1.4;
	
}

void System_TenCount::initiate_softStandingNumbers()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->softStanding[2][i] = 9;
		this->softStanding[1][i] = 9;
		this->softStanding[0][i] = -0.1;
	}
	
	this->softStanding[1][8] = -0.1;
	this->softStanding[1][9] = -0.1;
	this->softStanding[1][0] = -0.1;
}

void System_TenCount::initiate_hardDoublingDown()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->hardDoublingDown[6][i] = -0.1;
		this->hardDoublingDown[5][i] = -0.1;
		this->hardDoublingDown[4][i] = -0.1;
		this->hardDoublingDown[3][i] = -0.1;
		this->hardDoublingDown[2][i] = -0.1;
		this->hardDoublingDown[1][i] = -0.1;
		this->hardDoublingDown[0][i] = -0.1;
	}
	
	this->hardDoublingDown[5][1] = 0.9;
	this->hardDoublingDown[5][2] = 1.1;
	this->hardDoublingDown[5][3] = 1.2;
	this->hardDoublingDown[5][4] = 1.4;
	this->hardDoublingDown[5][5] = 1.4;
	
	this->hardDoublingDown[6][1] = 1.3;
	this->hardDoublingDown[6][2] = 1.5;
	this->hardDoublingDown[6][3] = 1.7;
	this->hardDoublingDown[6][4] = 2.0;
	this->hardDoublingDown[6][5] = 2.1;
	this->hardDoublingDown[6][6] = 1.0;
	
	this->hardDoublingDown[7][1] = 2.2;
	this->hardDoublingDown[7][2] = 2.4;
	this->hardDoublingDown[7][3] = 2.8;
	this->hardDoublingDown[7][4] = 3.3;
	this->hardDoublingDown[7][5] = 3.4;
	this->hardDoublingDown[7][6] = 2.0;
	this->hardDoublingDown[7][7] = 1.6;
	this->hardDoublingDown[7][8] = -0.1;
	this->hardDoublingDown[7][9] = -0.1;
	this->hardDoublingDown[7][0] = -0.1;
	
	this->hardDoublingDown[8][1] = 3.7;
	this->hardDoublingDown[8][2] = 4.2;
	this->hardDoublingDown[8][3] = 4.8;
	this->hardDoublingDown[8][4] = 5.6;
	this->hardDoublingDown[8][5] = 5.7;
	this->hardDoublingDown[8][6] = 3.8;
	this->hardDoublingDown[8][7] = 3.0;
	this->hardDoublingDown[8][8] = 2.5;
	this->hardDoublingDown[8][9] = 1.9;
	this->hardDoublingDown[8][0] = -0.1;
	
	this->hardDoublingDown[9][1] = 3.9;
	this->hardDoublingDown[9][2] = 4.2;
	this->hardDoublingDown[9][3] = 4.8;
	this->hardDoublingDown[9][4] = 5.5;
	this->hardDoublingDown[9][5] = 5.5;
	this->hardDoublingDown[9][6] = 3.7;
	this->hardDoublingDown[9][7] = 3.0;
	this->hardDoublingDown[9][8] = 2.6;
	this->hardDoublingDown[9][9] = 2.8;
	this->hardDoublingDown[9][0] = -0.1;
}

void System_TenCount::initiate_softDoublingDown()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->softDoublingDown[0][i] = -0.1;
	}
	
	for (i = 0 ; i <= 8 ; i++)
	{
		this->softDoublingDown[i][6] = -0.1;
		this->softDoublingDown[i][7] = -0.1;
		this->softDoublingDown[i][8] = -0.1;
		this->softDoublingDown[i][9] = -0.1;
		this->softDoublingDown[i][0] = -0.1;
	}
	
	this->softDoublingDown[1][1] = 1.5;
	this->softDoublingDown[1][2] = 1.7;
	this->softDoublingDown[1][3] = 2.1;
	this->softDoublingDown[1][4] = 2.6;
	this->softDoublingDown[1][5] = 2.7;
	
	this->softDoublingDown[2][1] = 1.5;
	this->softDoublingDown[2][2] = 1.8;
	this->softDoublingDown[2][3] = 2.3;
	this->softDoublingDown[2][4] = 2.9;
	this->softDoublingDown[2][5] = 3.0;
	
	this->softDoublingDown[3][1] = 1.6;
	this->softDoublingDown[3][2] = 1.9;
	this->softDoublingDown[3][3] = 2.4;
	this->softDoublingDown[3][4] = 3.0;
	this->softDoublingDown[3][5] = 3.2;
	
	this->softDoublingDown[4][1] = 1.6;
	this->softDoublingDown[4][2] = 1.9;
	this->softDoublingDown[4][3] = 2.5;
	this->softDoublingDown[4][4] = 3.1;
	this->softDoublingDown[4][5] = 4.0;
	
	this->softDoublingDown[5][1] = 2.1;
	this->softDoublingDown[5][2] = 2.5;
	this->softDoublingDown[5][3] = 3.2;
	this->softDoublingDown[5][4] = 4.8;
	this->softDoublingDown[5][5] = 4.8;
	this->softDoublingDown[5][6] = 1.1;
	
	this->softDoublingDown[6][1] = 2.0;
	this->softDoublingDown[6][2] = 2.2;
	this->softDoublingDown[6][3] = 3.3;
	this->softDoublingDown[6][4] = 3.8;
	this->softDoublingDown[6][5] = 3.5;
	
	this->softDoublingDown[7][1] = 1.4;
	this->softDoublingDown[7][2] = 1.7;
	this->softDoublingDown[7][3] = 1.8;
	this->softDoublingDown[7][4] = 2.0;
	this->softDoublingDown[7][5] = 2.0;
	
	this->softDoublingDown[8][1] = 1.3;
	this->softDoublingDown[8][2] = 1.3;
	this->softDoublingDown[8][3] = 1.5;
	this->softDoublingDown[8][4] = 1.6;
	this->softDoublingDown[8][5] = 1.6;
}

void System_TenCount::initiate_splittingPairs()
{
	int i = 0;
	
	for (i = 0 ; i <= 9 ; i++)
	{
		this->splittingPairs[0][i] = -0.1;
		this->splittingPairs[1][i] = -0.1;
		this->splittingPairs[2][i] = -0.1;
		this->splittingPairs[3][i] = -0.1;
		this->splittingPairs[4][i] = -0.1;
		this->splittingPairs[5][i] = 9;
		this->splittingPairs[6][i] = 9;
		this->splittingPairs[8][i] = -0.1;
	}
	
	this->splittingPairs[0][1] = 3.1;
	this->splittingPairs[0][2] = 3.8;
	this->splittingPairs[0][3] = 9;
	this->splittingPairs[0][4] = 9;
	this->splittingPairs[0][5] = 9;
	
	this->splittingPairs[1][1] = 9;
	this->splittingPairs[1][2] = 9;
	this->splittingPairs[1][3] = 9;
	this->splittingPairs[1][4] = 9;
	this->splittingPairs[1][5] = 9;
	
	this->splittingPairs[2][1] = 1.3;
	this->splittingPairs[2][2] = 1.6;
	this->splittingPairs[2][3] = 1.9;
	this->splittingPairs[2][4] = 2.4;
	this->splittingPairs[2][5] = 2.1;
	
	this->splittingPairs[4][1] = 2.4;
	this->splittingPairs[4][2] = 2.6;
	this->splittingPairs[4][3] = 3.0;
	this->splittingPairs[4][4] = 3.6;
	this->splittingPairs[4][5] = 4.1;
	this->splittingPairs[4][6] = 3.4;
	
	this->splittingPairs[5][8] = -0.1;
	this->splittingPairs[5][9] = -0.1;
	this->splittingPairs[5][0] = -0.1;
	
	this->splittingPairs[6][9] = -0.1;
	this->splittingPairs[6][0] = -0.1;
	
	this->splittingPairs[7][1] = 2.4;
	this->splittingPairs[7][2] = 2.8;
	this->splittingPairs[7][3] = 3.1;
	this->splittingPairs[7][4] = 3.7;
	this->splittingPairs[7][5] = 3.2;
	this->splittingPairs[7][6] = 1.6;
	this->splittingPairs[7][7] = 9;
	this->splittingPairs[7][8] = 4.2;
	this->splittingPairs[7][9] = -0.1;
	this->splittingPairs[7][0] = -0.1;
	
	this->splittingPairs[8][1] = 1.4;
	this->splittingPairs[8][2] = 1.5;
	this->splittingPairs[8][3] = 1.7;
	this->splittingPairs[8][4] = 1.9;
	this->splittingPairs[8][5] = 1.8;
	
	this->splittingPairs[9][1] = 4.0;
	this->splittingPairs[9][2] = 4.1;
	this->splittingPairs[9][3] = 4.5;
	this->splittingPairs[9][4] = 4.9;
	this->splittingPairs[9][5] = 5.0;
	this->splittingPairs[9][6] = 3.8;
	this->splittingPairs[9][7] = 3.3;
	this->splittingPairs[9][8] = 3.1;
	this->splittingPairs[9][9] = 3.2;
	this->splittingPairs[9][0] = -0.1;
}


