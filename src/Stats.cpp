#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "../headers/_variables.h"
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/Stats.h"


Stats::Stats()
{
	
}


Stats::~Stats()
{
	close(this->logFile);
}

void Stats::init(int playerValue, int dealerValue, bool softHand, int decisionConcerned, int decision, long int goal, char* filename)
{
	this->playerValue = playerValue;
	this->dealerValue = dealerValue;
	this->softHand = softHand;
	this->decisionConcerned = decisionConcerned;
	this->decision = decision;
	this->goal = goal;
	this->handsPlayed = 0;
	this->boxes = (bool*) calloc((MAX_SPLIT+1) * NB_BOXES, sizeof(bool));
	this->resetBoxes();
	this->wins = 0;
	this->loses = 0;
	this->ties = 0;
	this->startTime = 0;
	this->lastHandsPlayed = 0;
	this->lastTotalHandsPlayed = 0;
	
	if (!filename || strlen(filename) <= 0)
	{
		this->fileName = (char*)malloc(sizeof(char) * 2);
		this->fileName[0] = '\0';
		this->logFile = -1;
	}
	else
	{
		this->fileName = (char*)malloc(sizeof(char) * strlen(filename));
		this->fileName = filename;
		char src[50];
		sprintf(src, "output/%s", filename);
		this->logFile = open(src, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0755);
	}
}

void Stats::resetBoxes()
{
	for (int i = 0 ; i < (MAX_SPLIT+1) * NB_BOXES ; i++)
	{
		this->boxes[i] = false;
	}
}

int Stats::getPlayerValue()
{
	return this->playerValue;
}

int Stats::getDealerValue()
{
	return this->dealerValue;
}

int Stats::isSoftHand()
{
	return this->softHand;
}

int Stats::getDecisionConcerned()
{
	return this->decisionConcerned;
}

int Stats::getDecision()
{
	return this->decision;
}

long int Stats::getGoal()
{
	return this->goal;
}

void Stats::addBox(int boxIndex)
{
	if (this->finished() || this->boxes[boxIndex])
	{
		return;
	}
	this->boxes[boxIndex] = true;
	this->handsPlayed++;
}

bool Stats::isConcerned(int boxIndex)
{
	return this->boxes[boxIndex];
}

bool Stats::finished()
{
	return this->handsPlayed >= this->goal;
}

void Stats::printStatus(long int handsPlayed)
{
	this->printStatus(handsPlayed, true);
}

void Stats::printStatus(long int handsPlayed, bool doClear)
{
	char message[100];
	char decisionString[11];
	
	switch (this->decisionConcerned)
	{
		case DOUBLEDOWN:
			sprintf(decisionString, "DOUBLEDOWN");
			break;
		
		case SPLIT:
			sprintf(decisionString, "SPLIT");
			break;
		
		case DRAW:
		default:
			sprintf(decisionString, "DRAW");
			break;
	}
	
	if (doClear)
	{
		clear();
	}
	
	int currentTime = time(NULL);
	double deltaTime = ((((double)getMilliTime())/1000.0 - this->lastTime) <= 0) ? 1 : (((double)getMilliTime())/1000.0 - this->lastTime);
	
	double total = this->handsPlayed ? ((double) this->handsPlayed) : 100;
	
	double winPercentage = this->wins / total * 100;
	double tiePercentage = this->ties / total * 100;
	double losePercentage = this->loses / total * 100;
	
	int elapsedTimes = (currentTime - this->startTime > 0) ? currentTime - this->startTime : 1;
	int elapsedTimem = elapsedTimes / 60;
	int elapsedTimeh = elapsedTimes / 3600;
	
	int handsPerSecond = handsPlayed / elapsedTimes;
	int iHandsPerSecond = this->handsPlayed / elapsedTimes;
	int iHandsPerMinute = (this->handsPlayed*60) / elapsedTimes;
	
	int instantHPS = ((double)(handsPlayed - this->lastTotalHandsPlayed)) / deltaTime;
	int instantiHPS = ((double)(this->handsPlayed - this->lastHandsPlayed)) / deltaTime;
	int instantiHPM = ((double)(this->handsPlayed - this->lastHandsPlayed)*60) / deltaTime;
	
	int etaS = (this->goal - this->handsPlayed) / (instantiHPS ? instantiHPS : 1);
	int etaM = etaS / 60;
	int etaH = etaS / 3600;
	
	int etaAverageS = ((double)this->goal) / ((double)this->handsPlayed ? this->handsPlayed : 1) * ((double)elapsedTimes) - ((double)elapsedTimes);
	int etaAverageM = etaAverageS / 60;
	int etaAverageH = etaAverageS / 3600;
	
	double progress = ((double)this->handsPlayed*100.0) / ((double)this->goal);
	
	printHr(false);
	sprintf(message, "Testing %s %2d versus %2d on", this->softHand ? "soft" : "hard", this->playerValue, this->dealerValue);
	sprintf(message, "%s %10s (%2d)", message, decisionString, this->decision);
	printBars(message, true);
	
	printHr(false);
	
	sprintf(message, "Total Hands played :%'20ld", handsPlayed);
	sprintf(message, "%s    --> per second:  %'7d / %'5d", message, instantHPS, instantiHPS);
	printBars(message);
	
	sprintf(message, "Interesting Hands played :%'14d", this->handsPlayed);
	sprintf(message, "%s    --> per minute:          %'7d", message, instantiHPM);
	printBars(message);
	
	sprintf(message, "Goal :                    %'14ld", this->goal);
	sprintf(message, "%s    --> average (s): %'7d / %'5d", message, handsPerSecond, iHandsPerSecond);
	printBars(message);
	
	sprintf(message, "Interesting Hands frequency :    %5.2f %%", ((double)this->handsPlayed) * 100 / ((double)handsPlayed));
	sprintf(message, "%s    --> average (m):         %'7d", message, iHandsPerMinute);
	printBars(message);
	
	printBars((char*)"");
	
	sprintf(message, "Progress : [");
	for (int i = 0 ; i < TERMINAL_SIZE_X-26 ; i++)
	{
		if (i < (int)(progress * (TERMINAL_SIZE_X-26) / 100))
		{
			sprintf(message, "%s=", message);
		}
		else if (i == (int)(progress * (TERMINAL_SIZE_X-26) / 100))
		{
			sprintf(message, "%s>", message);
		}
		else
		{
			sprintf(message, "%s ", message);
		}
	}
	sprintf(message, "%s] %6.2f %%", message, progress);
	printBars(message);
	
	printBars((char*)"");
	
	sprintf(message, "Elapsed time :  %02d:%02d:%02d", elapsedTimeh%60, elapsedTimem % 60, elapsedTimes % 60);
	printBars(message);
	
	sprintf(message, "ETA :           %02d:%02d:%02d", etaH%60, etaM % 60, etaS % 60);
	printBars(message);
	
	sprintf(message, "ETA (on AVG) :  %02d:%02d:%02d", etaAverageH%60, etaAverageM % 60, etaAverageS % 60);
	printBars(message);
	
	printBars((char*)"");
	
	sprintf(message, "Wins :  %'13d (%5.2f %%)", this->wins, winPercentage);
	printBars(message);
	
	sprintf(message, "Ties :  %'13d (%5.2f %%)", this->ties, tiePercentage);
	printBars(message);
	
	sprintf(message, "Loses : %'13d (%5.2f %%)", this->loses, losePercentage);
	printBars(message);
	
	printBars((char*)"");
	
	if (doClear)
	{
		sprintf(message, "Interest index :  %2.8f", winPercentage - losePercentage);
	}
	if (!doClear)
	{
		sprintf(message, "Interest index :  %2.2f", winPercentage - losePercentage);
	}
	printBars(message);
	
	printHr(false);
	if (strlen(this->fileName) > 0)
	{
		sprintf(message, "Writing to file : output/%s", truncate(this->fileName, 51));
		printBars(message);
		printHr(false);
	}
	
	this->lastHandsPlayed = this->handsPlayed;
	this->lastTotalHandsPlayed = handsPlayed;
	this->lastTime = ((double)getMilliTime()) / 1000.0;
}

void Stats::setTime()
{
	this->startTime = time(NULL);
	this->lastTime = ((double)getMilliTime()) / 1000.0;
}

void Stats::update(int boxIndex, int status)
{
	this->boxes[boxIndex] = false;
	if (status == 1)
	{
		this->wins++;
	}
	if (status == 0)
	{
		this->ties++;
	}
	if (status == -1)
	{
		this->loses++;
	}
}

void Stats::write(int handsPlayed)
{
	if (this->logFile == -1)
	{
		return;
	}
	int stdoutCopy = dup(1);
	dup2(this->logFile, 1);
	this->printStatus(handsPlayed, false);
	dup2(stdoutCopy, 1);
}
