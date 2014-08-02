#include <stdio.h>
#include <stdlib.h>
#include "../headers/_variables.h"
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/GlobalCount.h"
#include "../headers/System_Dealer.h"
#include "../headers/Game.h"

extern GlobalCount count;
extern bool fffffffffff;
extern bool FORCEDEBUG;

Game::Game(Shoe* shoe)
{
	this->init(shoe, 5, 500, 7);
}

Game::Game(Shoe* shoe, int min, int max)
{
	this->init(shoe, min, max, 7);
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
	
	this->dealer = new Player((char*) "Dealer", -1, -1, new System_Dealer());
	this->dealerBox = new Box();
}

int Game::addPlayer(Player* player)
{
	this->players[this->nbPlayers] = player;
	return this->nbPlayers++;
}

void Game::resetBoxes()
{
	int i = 0;
	for (i = 0 ; i < this->nbBoxes + MAX_SPLIT * this->nbBoxes ; i++)
	{
		this->boxes[i].reset();
	}
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		this->splitIndexes[i] = 0;
	}
	this->dealerBox->reset();
}

void Game::initTurn()
{
	this->resetBoxes();
	this->dealerBox->take(this->dealer, 0);
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
	
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		
		this->deal(i);
	}
	
	this->deal(-1);
	
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		
		this->deal(i);
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
	
	Box* box = (boxIndex == -1) ? this->dealerBox : &this->boxes[boxIndex];
	
	while(!box->hand.isNatural() && !box->hand.isBusted() && (decision = box->decision(&this->dealerBox->hand, (boxIndex != -1 && this->splitIndexes[boxIndex % this->nbBoxes] < MAX_SPLIT), true)) != STAND)
	{
		if (box->hand.getValue() == 0) break;
		
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
			//printColor(C_RED + 10, (char*)"Couldn't double down !! Just drawed a card\n");
			//system("echo \"PAUSE\" && read a");
		}
		
		if (decision == SPLIT)
		{
			if (!this->boxes[boxIndex].hand.isPair())
			{
				printColor(C_RED + 10, (char*) "Tried to split a non Pair !!!!!!\n");
				system("echo \"PAUSE\" && read a");
			}
			if (boxIndex >= this->nbBoxes * MAX_SPLIT)
			{
				printColor(C_RED + 10, (char*) "Too many splits !!!!!!\n");
				system("echo \"PAUSE\" && read a");
			}
			
			
			//if ((DEBUG || FORCEDEBUG))printColor(C_YELLOW, (char*) "  --> Splitting that\n");
			//puts("  --> Splitting that");
			//system("echo \"PAUSE\" && read a");
			
			int splitIndex = ++this->splitIndexes[boxIndex % this->nbBoxes];
			
			int value = this->boxes[boxIndex].hand.getSoftValue() / 2;
			int bet = this->boxes[boxIndex].getBet();
			Player* player = this->boxes[boxIndex].player;
			int iIndex = 0;
			int splitBoxIndex = (boxIndex % this->nbBoxes) + (this->nbBoxes * splitIndex);
			
			//printf("[boxIndex: %d, this->nbBoxes: %d, splitIndex: %d, splitBoxIndex: %d]\n", boxIndex, this->nbBoxes, splitIndex, splitBoxIndex);
			
			//if (strcmp(player->getName(), "Don Self") == 0) fffffffffff = true;
			
			this->boxes[boxIndex].tie();
			this->boxes[boxIndex].reset();
			this->boxes[boxIndex].take(player, player->betAmount(bet), true);
			this->boxes[boxIndex].hand.add(value);
			
			this->boxes[splitBoxIndex].reset();
			this->boxes[splitBoxIndex].take(player, player->betAmount(bet), true);
			this->boxes[splitBoxIndex].hand.add(value);
			
			this->deal(boxIndex);
			this->deal(splitBoxIndex);
			
			iIndex = boxIndex;
			if (value != 1 || (this->boxes[iIndex].hand.isPair() && this->splitIndexes[iIndex % this->nbBoxes] < MAX_SPLIT))
			{
				this->decision(iIndex);
			}
			iIndex = splitBoxIndex;
			if (value != 1 || (this->boxes[iIndex].hand.isPair() && this->splitIndexes[iIndex % this->nbBoxes] < MAX_SPLIT))
			{
				this->decision(iIndex);
			}
			
			//system("echo \"Splitted. PAUSE\" && read a");
			
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

int Game::play()
{
	int handsPlayed = 0;
	while (1)
	{
		if ((DEBUG || FORCEDEBUG))puts("Initializing shoe...");
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
			if ((DEBUG || FORCEDEBUG))puts("Initializing turn...");
			this->initTurn();
			
			if ((DEBUG || FORCEDEBUG))puts("-Betting...");
			this->bet();
			if ((DEBUG || FORCEDEBUG))puts("-Dealing first wave...");
			this->deal();
			
			if (this->dealerBox->hand.getSoftValue() == 1)
			{
				if ((DEBUG || FORCEDEBUG))puts("-Insurance...");
				this->insurance();
			}
			
			if ((DEBUG || FORCEDEBUG))puts("-Dealing second wave...");
			this->decisions();
			
			if ((DEBUG || FORCEDEBUG))puts("-Paying players...");
			this->pay();
			
			if (this->dealerBox->hand.isNatural())
			{
				if ((DEBUG || FORCEDEBUG))puts("-Paying insurance...");
				this->payInsurance();
			}
			
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
			
			if(PAUSE || FORCEDEBUG)system("echo \"PAUSE\" && read a");
			else if (SLEEP)sleep(1);
			
			if (fffffffffff)
			{
				system("echo \"PAUSE\" && read a");
				fffffffffff = false;
			}
			
		}
	}
}

