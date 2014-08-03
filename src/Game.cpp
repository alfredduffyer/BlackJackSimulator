#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

extern GlobalCount count;
extern bool FORCEDEBUG;
extern Stats stats;

Game::Game(Shoe* shoe)
{
	this->init(shoe, 5, 500, NB_BOXES);
}

Game::Game(Shoe* shoe, int min, int max)
{
	this->init(shoe, min, max, NB_BOXES);
}

Game::Game(Shoe* shoe, int min, int max, int nbBoxes)
{
	this->init(shoe, min, max, nbBoxes);
}

void Game::init(Shoe* shoe, int min, int max, int nbBoxes)
{
	this->shoe = shoe;
	this->min = min;
	this->max = max;
	this->nbBoxes = nbBoxes;
	this->nbPlayers = 0;
	
	this->players = (Player**) malloc(this->nbBoxes * sizeof(Player*));
	this->boxes = (Box*) malloc((MAX_SPLIT * this->nbBoxes + this->nbBoxes) * sizeof(Box));
	this->splitIndexes = (int*) malloc(sizeof(int) * this->nbBoxes);
	
	this->dealerBox = new Box();
	this->dealerBox->take(new Player((char*) "Dealer", -1, -1, new System_Dealer()), 0);
}

int Game::addPlayer(Player* player)
{
	if (this->nbPlayers >= this->nbBoxes)
	{
		return this->nbPlayers;
	}
	this->players[this->nbPlayers++] = player;
	return this->nbPlayers;
}

void Game::resetBoxes()
{
	int i = 0;
	for (i = 0 ; i < this->nbBoxes + MAX_SPLIT * this->nbBoxes ; i++)
	{
		this->boxes[i].reset();
		if (i < this->nbBoxes)
		{
			this->splitIndexes[i] = 0;
		}
	}
	this->dealerBox->hand.reset();
}

int Game::howManyHands(bool isMainPlayer, Player* player)
{
	if (!isMainPlayer && random(1, 100) > GAME_PLAYING) return 0;
	return player->howManyHands(this->nbBoxes);
}

void Game::bet()
{
	int i = 0, j = 0, k = 0, handsnumber = this->howManyHands(true, this->players[0]), currentBox = 0;
	
	for (i = 0 ; i < handsnumber ; i++)
	{
		currentBox = (this->nbBoxes/2 + i) % this->nbBoxes;
		
		if (this->boxes[currentBox].isFree())
		{
			this->boxes[currentBox].take(this->players[0], this->players[0]->bet());
		}
	}
	
	currentBox = random(0, this->nbBoxes-1);
	
	for (i = 1 ; i < this->nbPlayers ; i++)
	{
		handsnumber = this->howManyHands(false, this->players[i]);
		
		for (j = 0 ; j < handsnumber ; j++)
		{
			for (k = 0 ; k < 3 ; k++)
			{
				if (this->boxes[currentBox].isFree())
				{
					this->boxes[currentBox].take(this->players[i], this->players[i]->bet());
					break;
				}
				currentBox = (currentBox + (this->nbBoxes / 2 + 1)) % this->nbBoxes;
			}
		}
	}
	
	if (DEBUG || FORCEDEBUG)
	{
		for (i = 0 ; i < this->nbBoxes ; i++)
		{
			printf(" [%d] total bet is %d", i, this->boxes[i].getBet());
			if (!this->boxes[i].isFree())
			{
				printf(" (%s)", this->boxes[i].player->getName());
			}
			puts("");
		}
	}
	
}

void Game::deal(int boxIndex)
{
	Card card = this->shoe->top();
	char message[100], splitMessage[30];
	
	sprintf(splitMessage, "%s", (boxIndex >= this->nbBoxes) ? " |\n ----->" : "");
	
	if (boxIndex >= 0)
	{
		this->boxes[boxIndex].hand.add(card.value);
		sprintf(message, "%s [%d] gets a %d, total is now %d (%s)\n", splitMessage, boxIndex, card.value, this->boxes[boxIndex].hand.getValue(), this->boxes[boxIndex].player->getName());
		if ((DEBUG || FORCEDEBUG) && strcmp(this->boxes[boxIndex].player->getName(), (char*) "Don Self"))printColor(C_RED, message);
		else if ((DEBUG || FORCEDEBUG))printf("%s", message);
	}
	else
	{
		this->dealerBox->hand.add(card.value);
		if ((DEBUG || FORCEDEBUG))printf("%s DDD gets a %d, total is now %d (%s)\n", splitMessage, card.value, this->dealerBox->hand.getValue(), this->dealerBox->player->getName());
	}
}

void Game::deal()
{
	int i = 0;
	
	for (i = 0 ; i < this->nbBoxes*2 ; i++)
	{
		if (i == this->nbBoxes)
		{
			this->deal(-1);
		}
		
		if (this->boxes[i % this->nbBoxes].isFree())
		{
			continue;
		}
		
		this->deal(i % this->nbBoxes);
	}
}

void Game::insurance()
{
	int i = 0;
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		if (this->boxes[i].insure())
		{
			if ((DEBUG || FORCEDEBUG)) printf(" [%d] took insurance\n", i);
		}
	}
}

void Game::decision(int boxIndex)
{
	int decision = 0;
	bool canSplit = (boxIndex != -1 && this->splitIndexes[boxIndex % this->nbBoxes] < MAX_SPLIT);
	
	Box* box = (boxIndex == -1) ? this->dealerBox : &this->boxes[boxIndex];
	
	while (!box->hand.isNatural() && !box->hand.isBusted())
	{
		decision = box->decision(&this->dealerBox->hand, canSplit, true);
		
		if (strcmp(box->player->getName(), (char*) "Don Self") && box->hand.getValue() == stats.getPlayerValue() && this->dealerBox->hand.getValue() == stats.getDealerValue())
		{
			bool matchSplitStat = stats.getDecisionConcerned() == SPLIT && canSplit;
			bool matchDoubleDownStat = stats.getDecisionConcerned() == DOUBLEDOWN && box->hand.getSize() == 2 && (decision == DOUBLEDOWN || decision == DRAW || decision == STAND);
			bool matchDrawStat = stats.getDecisionConcerned() == DRAW && (decision == DRAW || decision == STAND);
			
			if (matchSplitStat || matchDoubleDownStat || matchDrawStat)
			{
				stats.addBox(boxIndex);
				//FORCEDEBUG = true;
			}
		}
		
		if (decision == STAND)
		{
			break;
		}
		
		if (decision == DRAW)
		{
			this->deal(boxIndex);
		}
		
		if (decision == DOUBLEDOWN)
		{
			this->deal(boxIndex);
			if (box->doubleDown() > 0)
			{
				break;
			}
		}
		
		if (decision == SPLIT)
		{
			int splitIndex = ++this->splitIndexes[boxIndex % this->nbBoxes];
			
			int value = this->boxes[boxIndex].hand.getSoftValue() / 2;
			int bet = this->boxes[boxIndex].getBet();
			Player* player = this->boxes[boxIndex].player;
			int splitBoxIndex = (boxIndex % this->nbBoxes) + (this->nbBoxes * splitIndex);
			
			this->boxes[boxIndex].tie();
			this->boxes[boxIndex].reset();
			this->boxes[boxIndex].take(player, player->betAmount(bet), true);
			this->boxes[boxIndex].hand.add(value);
			
			this->boxes[splitBoxIndex].reset();
			this->boxes[splitBoxIndex].take(player, player->betAmount(bet), true);
			this->boxes[splitBoxIndex].hand.add(value);
			
			this->deal(boxIndex);
			this->deal(splitBoxIndex);
			
			if (value != 1 || (this->boxes[boxIndex].hand.isPair() && this->splitIndexes[boxIndex % this->nbBoxes] < MAX_SPLIT))
			{
				this->decision(boxIndex);
			}
			if (value != 1 || (this->boxes[splitBoxIndex].hand.isPair() && this->splitIndexes[splitBoxIndex % this->nbBoxes] < MAX_SPLIT))
			{
				this->decision(splitBoxIndex);
			}
			
			break;
		}
	}
}

void Game::decisions()
{
	int i = 0;
	
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		this->decision(i);
	}
	
	this->decision(-1);
}

void Game::payInsurance()
{
	int i = 0;
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree() || !this->boxes[i].hasInsured())
		{
			continue;
		}
		if ((DEBUG || FORCEDEBUG)) printf(" [%d] Paying insurance\n", i);
		if ((DEBUG || FORCEDEBUG)) printf("  --> Had %1.1f, has now ", this->boxes[i].player->getStack());
		this->boxes[i].payInsurance();
		if ((DEBUG || FORCEDEBUG)) printf("%1.1f\n", this->boxes[i].player->getStack());
	}
}

void Game::pay()
{
	int i = 0, status = 0;
	char text1[100], text2[50], text3[50];
	
	for (i = this->nbBoxes + MAX_SPLIT * this->nbBoxes - 1 ; i >= 0 ; i--)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		
		status = this->boxes[i].hand.beats(&this->dealerBox->hand);
		
		if (stats.isConcerned(i))
		{
			stats.update(i, status);
		}
		
		sprintf(text1, " [%d] has %d against %d, status is %d (%s)\n", i, this->boxes[i].hand.getValue(), this->dealerBox->hand.getValue(), status, this->boxes[i].player->getName());
		sprintf(text2, "  --> Had %1.1f, has now ", this->boxes[i].player->getStack());
		
		if (status == 0)
		{
			this->boxes[i].tie();
		}
		if (status == 1)
		{
			this->boxes[i].win();
		}
		
		sprintf(text3, "%1.1f\n", this->boxes[i].player->getStack());
		
		if ((DEBUG || FORCEDEBUG) && strcmp(this->boxes[i].player->getName(), (char*) "Don Self"))
		{
			printColor(C_RED, text1);
			printColor(C_RED, text2);
			printColor(C_RED, text3);
		}
		else if ((DEBUG || FORCEDEBUG))
		{
			printf("%s", text1);
			printf("%s", text2);
			printf("%s", text3);
		}
	}
}

void Game::playStats(System* system)
{
	int handsPlayed = 0;
	int timestamp = time(NULL);
	this->addPlayer(new Player((char*) "Don Self", 1000, 5, system));
	this->addPlayer(new Player((char*) "The Player Who Never Busts", -1, 5, new System_ThePlayerWhoNeverBusts()));
	this->addPlayer(new Player((char*) "Mimic The Dealer", -1, 5, new System_Dealer()));
	this->addPlayer(new Player((char*) "The Random Player", -1, 5, new System_RandomPlayer()));
	
	while (!stats.finished())
	{
		this->shoe->reset();
		
		while (!this->shoe->isTheEnd())
		{
			if (!STATUS && time(NULL) != timestamp)
			{
				timestamp = time(NULL);
				printf("[");
				printNumber(handsPlayed);
				printf("] --> ");
				stats.printStatus();
			}
			
			handsPlayed++;
			FORCEDEBUG = false;
			
			if ((DEBUG || FORCEDEBUG)) count.printStatus();
			
			this->resetBoxes();
			stats.resetBoxes();
			
			debug((char*)"-Betting...\n");
			this->bet();
			
			debug((char*)"-Dealing first wave...\n");
			this->deal();
			
			if (this->dealerBox->hand.getSoftValue() == 1)
			{
				debug((char*)"-Insurance...\n");
				this->insurance();
			}
			
			debug((char*)"-Dealing second wave...\n");
			this->decisions();
			
			if (this->dealerBox->hand.isNatural())
			{
				debug((char*)"-Paying insurance...\n");
				this->payInsurance();
			}
			
			debug((char*)"-Paying players...\n");
			this->pay();
			
			if ((DEBUG || FORCEDEBUG)) printf("\n%d cards played, going to %d.\n\n", this->shoe->getIndex(), this->shoe->getLimit());
			
			if (STATUS) printf("[%d] Don Self has now %1.1f\n", handsPlayed, this->players[0]->getStack());
			if (this->players[0]->getStack() < this->players[0]->getUnit() * MAX_HAND_VARIATION * MAX_BET_VARIATION)
			{
				this->players[0] = new Player((char*) "Don Self", 1000, 5, system);
				if ((DEBUG || FORCEDEBUG)) printf("+++++++[%d] Don Self has now %1.1f\n", handsPlayed, this->players[0]->getStack());
			}
			
			if ((DEBUG || FORCEDEBUG)) stats.printStatus();
			
			if (PAUSE || FORCEDEBUG) spause();
			else if (SLEEP) sleep(1);
		}
	}
}

int Game::play()
{
	int handsPlayed = 0;
	while (1)
	{
		debug((char*)"Initializing shoe...\n");
		this->shoe->reset();
		
		while (!this->shoe->isTheEnd())
		{
			FORCEDEBUG = false;
			if (FORCE_DEBUG)
			{
				double nbBets = (double)this->players[0]->bet();
				FORCEDEBUG = (nbBets > 5);
				this->players[0]->win(nbBets);
			}
			
			if ((DEBUG || FORCEDEBUG)) count.printStatus();
			
			handsPlayed++;
			debug((char*)"Initializing turn...\n");
			this->resetBoxes();
			
			debug((char*)"-Betting...\n");
			this->bet();
			debug((char*)"-Dealing first wave...\n");
			this->deal();
			
			if (this->dealerBox->hand.getSoftValue() == 1)
			{
				debug((char*)"-Insurance...\n");
				this->insurance();
			}
			
			debug((char*)"-Dealing second wave...\n");
			this->decisions();
			
			if (this->dealerBox->hand.isNatural())
			{
				debug((char*)"-Paying insurance...\n");
				this->payInsurance();
			}
			
			debug((char*)"-Paying players...\n");
			this->pay();
			
			if ((DEBUG || FORCEDEBUG))printf("\n%d cards played, going to %d.\n\n", this->shoe->getIndex(), this->shoe->getLimit());
			
			for (int i = 0 ; i < this->nbBoxes ; i++)
			{
				if (!this->boxes[i].isFree() && strcmp(this->boxes[i].player->getName(), (char*) "Don Self"))
				{
					if(STATUS) printf("[%d] Don Self has now %1.1f\n", handsPlayed, this->boxes[i].player->getStack());
					else if((handsPlayed % 100000) == 0)printf("[%3ld %03d %03d %03d] Don Self has now %3ld %03d %03d %03d\n", (handsPlayed%1000000000000) / 1000000000, (handsPlayed%1000000000) / 1000000, (handsPlayed%1000000) / 1000, handsPlayed%1000, (((long int)this->boxes[i].player->getStack())%1000000000000) / 1000000000, (((int)this->boxes[i].player->getStack())%1000000000) / 1000000, (((int)this->boxes[i].player->getStack())%1000000) / 1000, ((int)this->boxes[i].player->getStack())%1000);
					if (this->boxes[i].player->getStack() < 5 || (handsPlayed >= NOSTATUSLIMIT))
					{
						return handsPlayed;
					}
					break;
				}
			}
			
			if(PAUSE || FORCEDEBUG) system("echo \"PAUSE\" && read a");
			else if (SLEEP)sleep(1);
		}
	}
}

void Game::playInf(System* system, double stack, int unit)
{
	int result = 0, nbPlays = 0;
	long int totalHandsPlayed = 0;
	double average = 0;
	char message[100];
	
	while (++nbPlays)
	{
		this->init(new Shoe(), 5, 500, NB_BOXES);
		this->addPlayer(new Player((char*) "Don Self", stack, unit, system));
		this->addPlayer(new Player((char*) "The Player Who Never Busts", -1, 5, new System_ThePlayerWhoNeverBusts()));
		this->addPlayer(new Player((char*) "Mimic The Dealer", -1, 5, new System_Dealer()));
		this->addPlayer(new Player((char*) "The Random Player", -1, 5, new System_RandomPlayer()));
		
		result = this->play();
		totalHandsPlayed += (long int) result;
		
		if (result != NOSTATUSLIMIT)
		{
			average = ((double) (average * (nbPlays-1) + result)) / ((double) nbPlays);
		}
		
		sprintf(message, "Don Self died in %9d hands, average is %5.0f, total %5d %03d %03d\n", result, average, (int) ((totalHandsPlayed-totalHandsPlayed % 1000000) / 1000000), (int) ((totalHandsPlayed % 1000000) / 1000), (int) (totalHandsPlayed % 1000));
		
		if (result == NOSTATUSLIMIT)
		{
			sprintf(message, "Don Self survived %9d hands, won a lot of money !\n", result);
			printColor(C_GREEN, message);
		}
		else
		{
			printColor(C_RED, message);
		}
		
		if (STATUS) break;
	}
}
