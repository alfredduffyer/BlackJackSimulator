#include <stdio.h>
#include "../headers/_variables.h"
#include "../headers/functions.h"
#include "../headers/System_RandomPlayer.h"

System_RandomPlayer::System_RandomPlayer() : System()
{
	
}

int System_RandomPlayer::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (canSplit && (player->getSoftValue() == 2 || player->getSoftValue() == 16) && dealer->getSoftValue() != 1)
	{
		if (DEBUG) printf("  --> Splitting a (%d,%d) against a %d\n", player->getSoftValue()/2, player->getSoftValue()/2, dealer->getSoftValue());
		return SPLIT;
	}
	
	if (canDoubleDown && ((player->getValue() == 11 && dealer->getSoftValue() != 1) || (player->getValue() == 10 && dealer->getSoftValue() < 10 && dealer->getSoftValue() != 1)))
	{
		if (DEBUG) printf("  --> Doubling down a %d against a %d\n", player->getValue(), dealer->getSoftValue());
		return DOUBLEDOWN;
	}
	
	if (player->isSoft() && player->getValue() < 17)
	{
		return DRAW;
	}
	if (player->isSoft() && player->getValue() == 17)
	{
		return (random(1,100) < 50) ? DRAW : STAND;
	}
	if (player->isSoft())
	{
		return STAND;
	}
	
	if (dealer->getSoftValue() == 1 || dealer->getSoftValue() == 10)
	{
		return (player->getValue() < 17) ? DRAW : STAND;
	}
	else if (dealer->getSoftValue() < 7)
	{
		return (player->getValue() < 14) ? DRAW : STAND;
	}
	
	return (player->getValue() < random(14, 17)) ? DRAW : STAND;
}
