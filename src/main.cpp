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
Stats stats;

int main(int argc, char* argv[])
{
	srand(getMilliTime());
	setlocale(LC_ALL, "");
	
	/*
	int player = 0, dealer = 0, decision = 0, replacement = 0;
	bool soft = false;
	char filename[200];
	*/
	
	int status = 0;
	long int goal = 0;
	char test = 'H';
	
	if (!initParams(argc, argv, &status, &goal, &test))
	{
		puts("Error found in params reading. Exiting...");
		return 1;
	}
	
	/*
	if (!initParams(argc, argv, &player, &dealer, &soft, &decision, &replacement, &goal, filename))
	{
		puts("Error found in params reading. Exiting...");
		return 1;
	}
	
	stats.init(player, dealer, soft, decision, replacement, goal, filename);
	*/
	
	Game game;
	//game.playInf(new System_BasicStrategy(), 1000, 5);
	//game.playInf(new System_SimplePointCount(), 10000, 5);
	
	/**/
	if (test == 'S') {		// S = Soft Standing Numbers
		game.testSS(new System_BasicStrategy(), status, goal);
	} else if (test == 'D') {	// D = Hard Double Down
		game.testHDD(new System_BasicStrategy(), status, goal);
	} else if (test == 'E') {	// E = Soft Double Down
		game.testSDD(new System_BasicStrategy(), status, goal);
	} else if (test == 'P') {	// P = Split
		game.testSP(new System_BasicStrategy(), status, goal);
	} else {			// H = Hard Standing Numbers
		game.testHS(new System_BasicStrategy(), status, goal);
	}
	/**/
}
