#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
#include "../headers/Stats.h"

GlobalCount count;
bool FORCEDEBUG = false;
Stats stats(12, 2, false, DRAW, 1, 1000000);

int main()
{
	srand(getMilliTime());
	setlocale(LC_ALL, "");
	
	Game game(new Shoe(), 5, 500, NB_BOXES);
	//game.playInf(new System_BasicStrategy(), 1000, 5);
	//game.playInf(new System_SimplePointCount(), 1000, 5);
	//game.playInf(new System_FullPointCount(), 1000, 5);
	//game.playInf(new System_TenCount(), 1000, 5);
	
	game.playStats(new System_BasicStrategy());
	
	return 1;
}
