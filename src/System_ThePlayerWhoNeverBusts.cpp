#include <stdio.h>
#include "../headers/_variables.h"
#include "../headers/functions.h"
#include "../headers/System_ThePlayerWhoNeverBusts.h"

System_ThePlayerWhoNeverBusts::System_ThePlayerWhoNeverBusts() : System()
{
	
}

int System_ThePlayerWhoNeverBusts::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (canSplit && (player->getSoftValue() == 2 || player->getSoftValue() == 16) && dealer->getSoftValue() != 1)
	{
		return SPLIT;
	}
	
	if (canDoubleDown && player->getValue() == 11 && dealer->getSoftValue() != 1)
	{
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
