#include <stdio.h>
#include <stdlib.h>
#include "../headers/_variables.h"
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/GlobalCount.h"
#include "../headers/System_BasicStrategy.h"
#include "../headers/System_Dealer.h"
#include "../headers/System_RandomPlayer.h"
#include "../headers/System_ThePlayerWhoNeverBusts.h"
#include "../headers/System_SimplePointCount.h"
#include "../headers/System_FullPointCount.h"
#include "../headers/System_TenCount.h"
#include "../headers/Game.h"

GlobalCount count;
bool FORCEDEBUG = false;

int main()
{
	srand(getMilliTime());
	
	Game game(new Shoe(), 5, 500, 7);
	//game.playInf(new System_BasicStrategy(), 1000, 5);
	//game.playInf(new System_SimplePointCount(), 1000, 5);
	//game.playInf(new System_FullPointCount(), 1000, 5);
	game.playInf(new System_TenCount(), 1000, 5);
	
	return 1;
}
