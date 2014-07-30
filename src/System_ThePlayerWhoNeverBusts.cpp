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
#include "../headers/System_ThePlayerWhoNeverBusts.h"

System_ThePlayerWhoNeverBusts::System_ThePlayerWhoNeverBusts() : System()
{
	
}

int System_ThePlayerWhoNeverBusts::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (canSplit && (player->getSoftValue() == 2 || player->getSoftValue() == 16) && dealer->getSoftValue() != 1)
	{
		if (DEBUG) printf("  --> Splitting a (%d,%d) against a %d\n", player->getSoftValue()/2, player->getSoftValue()/2, dealer->getSoftValue());
		return SPLIT;
	}
	
	if (canDoubleDown && player->getValue() == 11 && dealer->getSoftValue() != 1)
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
	
	return (!player->isSoft() && player->getValue() < 12) ? DRAW : STAND;
}
