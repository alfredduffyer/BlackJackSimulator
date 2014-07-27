#include <iostream>
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
#include "../headers/System_BasicStrategy.h"
#include "../headers/System_Dealer.h"
#include "../headers/System_RandomPlayer.h"
#include "../headers/System_ThePlayerWhoNeverBusts.h"
#include "../headers/System_SimplePointCount.h"
#include "../headers/System_FullPointCount.h"
#include "../headers/System_TenCount.h"
#include "../headers/Player.h"
#include "../headers/Box.h"
#include "../headers/Game.h"
#include <string.h>

extern GlobalCount count;
extern bool fffffffffff;

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

Game::~Game()
{
	
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

int Game::removePlayer()
{
	return --this->nbPlayers;
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


void Game::initShoe()
{
	this->shoe->reset();
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
	
	if (DEBUG)
	{
		for (i = 0 ; i < this->nbBoxes ; i++)
		{
			printf(" [%d] total bet is %d", i, this->boxes[i].getBet());
			if (!this->boxes[i].isFree())
			{
				printf(" (%s)", this->boxes[i].getName());
			}
			puts("");
		}
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

Box Game::deal(int boxIndex)
{
	Card card = this->shoe->top();
	char message[100], splitMessage[30];
	
	sprintf(splitMessage, "%s", (boxIndex >= this->nbBoxes) ? " |\n ----->" : "");
	
	if (boxIndex >= 0)
	{
		this->boxes[boxIndex].add(card.value);
		sprintf(message, "%s [%d] gets a %d, total is now %d (%s)\n", splitMessage, boxIndex, card.value, this->boxes[boxIndex].getValue(), this->boxes[boxIndex].getName());
		if (DEBUG && strcmp(this->boxes[boxIndex].getName(), (char*) "Don Self") == 0)printColor(C_RED, message);
		else if (DEBUG)printf("%s", message);
		return this->boxes[boxIndex];
	}
	else
	{
		this->dealerBox->add(card.value);
		if (DEBUG)printf("%s DDD gets a %d, total is now %d (%s)\n", splitMessage, card.value, this->dealerBox->getValue(), this->dealerBox->getName());
		return *this->dealerBox;
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

void Game::decision(int boxIndex)
{
	int decision = 0;
	
	Box* box = (boxIndex == -1) ? this->dealerBox : &this->boxes[boxIndex];
	
	while(!box->isNatural() && !box->isBusted() && (decision = box->decision(this->dealerBox->getHand(), (boxIndex != -1 && this->splitIndexes[boxIndex % this->nbBoxes] < MAX_SPLIT), true)) != STAND)
	{
		if (box->getValue() == 0) break;
		
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
			if (!this->boxes[boxIndex].getHand()->isPair())
			{
				printColor(C_RED + 10, (char*) "Tried to split a non Pair !!!!!!\n");
				system("echo \"PAUSE\" && read a");
			}
			if (boxIndex >= this->nbBoxes * MAX_SPLIT)
			{
				printColor(C_RED + 10, (char*) "Too many splits !!!!!!\n");
				system("echo \"PAUSE\" && read a");
			}
			
			
			//if (DEBUG)printColor(C_YELLOW, (char*) "  --> Splitting that\n");
			//puts("  --> Splitting that");
			//system("echo \"PAUSE\" && read a");
			
			int splitIndex = ++this->splitIndexes[boxIndex % this->nbBoxes];
			
			int value = this->boxes[boxIndex].getHand()->getSoftValue() / 2;
			int bet = this->boxes[boxIndex].getBet();
			Player* player = this->boxes[boxIndex].getPlayer();
			int iIndex = 0;
			int splitBoxIndex = (boxIndex % this->nbBoxes) + (this->nbBoxes * splitIndex);
			
			//printf("[boxIndex: %d, this->nbBoxes: %d, splitIndex: %d, splitBoxIndex: %d]\n", boxIndex, this->nbBoxes, splitIndex, splitBoxIndex);
			
			//if (strcmp(player->getName(), "Don Self") == 0) fffffffffff = true;
			
			this->boxes[boxIndex].tie();
			this->boxes[boxIndex].reset();
			this->boxes[boxIndex].take(player, player->betAmount(bet), true);
			this->boxes[boxIndex].add(value);
			
			this->boxes[splitBoxIndex].reset();
			this->boxes[splitBoxIndex].take(player, player->betAmount(bet), true);
			this->boxes[splitBoxIndex].add(value);
			
			this->deal(boxIndex);
			this->deal(splitBoxIndex);
			
			iIndex = boxIndex;
			if (value != 1 || (this->boxes[iIndex].getHand()->isPair() && this->splitIndexes[iIndex % this->nbBoxes] < MAX_SPLIT))
			{
				this->decision(iIndex);
			}
			iIndex = splitBoxIndex;
			if (value != 1 || (this->boxes[iIndex].getHand()->isPair() && this->splitIndexes[iIndex % this->nbBoxes] < MAX_SPLIT))
			{
				this->decision(iIndex);
			}
			
			//system("echo \"Splitted. PAUSE\" && read a");
			
			break;
		}
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
		
		status = this->boxes[i].getHand()->beats(this->dealerBox->getHand());
		
		sprintf(text1, " [%d] has %d against %d, status is %d (%s)\n", i, this->boxes[i].getValue(), this->dealerBox->getValue(), status, this->boxes[i].getName());
		sprintf(text2, "  --> Had %1.1f, has now ", this->boxes[i].getStack());
		
		if (status == 0)
		{
			this->boxes[i].tie();
		}
		if (status == 1)
		{
			this->boxes[i].win();
		}
		
		sprintf(text3, "%1.1f\n", this->boxes[i].getStack());
		
		if (DEBUG && strcmp(this->boxes[i].getName(), "Don Self") == 0)
		{
			printColor(C_RED, text1);
			printColor(C_RED, text2);
			printColor(C_RED, text3);
		}
		else if (DEBUG)
		{
			printf("%s", text1);
			printf("%s", text2);
			printf("%s", text3);
		}
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
			if (DEBUG) printf(" [%d] took insurance\n", i);
		}
	}
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
		if (DEBUG) printf(" [%d] Paying insurance\n", i);
		printf("  --> Had %1.1f, has now ", this->boxes[i].getStack());
		this->boxes[i].payInsurance();
		printf("%1.1f\n", this->boxes[i].getStack());
	}
}

int Game::play()
{
	int handsPlayed = 0;
	while (1)
	{
		if (DEBUG)puts("Initializing shoe...");
		this->initShoe();
		
		while (!this->shoe->isTheEnd())
		{
			handsPlayed++;
			if (DEBUG)puts("Initializing turn...");
			this->initTurn();
			
			if (DEBUG)puts("-Betting...");
			this->bet();
			if (DEBUG)puts("-Dealing first wave...");
			this->deal();
			
			if (this->dealerBox->getSoftValue() == 1)
			{
				if (DEBUG)puts("-Insurance...");
				this->insurance();
			}
			
			if (DEBUG)puts("-Dealing second wave...");
			this->decisions();
			
			if (DEBUG)puts("-Paying players...");
			this->pay();
			
			if (this->dealerBox->isNatural())
			{
				if (DEBUG)puts("-Paying insurance...");
				this->payInsurance();
			}
			
			if (DEBUG)printf("\n%d cards played, going to %d.\n\n", this->shoe->getIndex(), this->shoe->getLimit());
			
			for (int i = 0 ; i < this->nbBoxes ; i++)
			{
				if (!this->boxes[i].isFree() && strcmp(this->boxes[i].getName(), "Don Self") == 0)
				{
					if(STATUS) printf("[%d] Don Self has now %1.1f\n", handsPlayed, this->boxes[i].getStack());
					else if((handsPlayed % 100000) == 0)printf("[%3ld %03d %03d %03d] Don Self has now %3ld %03d %03d %03d\n", (handsPlayed%1000000000000) / 1000000000, (handsPlayed%1000000000) / 1000000, (handsPlayed%1000000) / 1000, handsPlayed%1000, (((long int)this->boxes[i].getStack())%1000000000000) / 1000000000, (((int)this->boxes[i].getStack())%1000000000) / 1000000, (((int)this->boxes[i].getStack())%1000000) / 1000, ((int)this->boxes[i].getStack())%1000);
					if (this->boxes[i].getStack() < 5 || handsPlayed > 2000000)
					{
						return handsPlayed;
					}
					break;
				}
			}
			
			if(PAUSE)system("echo \"PAUSE\" && read a");
			else if (SLEEP)sleep(1);
			
			if (fffffffffff)
			{
				system("echo \"PAUSE\" && read a");
				fffffffffff = false;
			}
			
		}
	}
}
