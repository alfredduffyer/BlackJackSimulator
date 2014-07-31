#include "../headers/_variables.h"
#include "../headers/System_Dealer.h"

System_Dealer::System_Dealer() : System()
{
	
}

int System_Dealer::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (dealer->getValue() && canSplit && canDoubleDown){}
	return (player->getValue() < 17) ? DRAW : STAND;
}
