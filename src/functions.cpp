#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>
#include "../headers/_variables.h"

int strlen(char* str)
{
	int i = 0;
	while (str[i++] != '\0');
	return i-1;
}

bool strcmp(char* str1, char* str2)
{
	for (int i = 0 ; i < strlen(str1) && i < strlen(str2) ; i++)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}
	
	return true;
}

void sleep(int seconds)
{
	char command[15];
	sprintf(command, "sleep %d", seconds);
	system(command);
}

void spause()
{
	system("echo \"PAUSE\" && read a");
}

void clear()
{
	system("clear");
}

int random(int min, int max)
{
	// TODO : Better random
	return rand() % (max - min + 1) + min;
}

void addToFile(char* fileName, char* str)
{
	FILE* fichier = NULL;
	char filePath[50];
	
	sprintf(filePath, "output/%s", fileName);
	
	fichier = fopen(filePath, "a+");
	fprintf(fichier, "%s", str);
	fclose(fichier);
}

long int getMilliTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (long int) (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

char* generateFileName(int player, int dealer, bool soft, int decision, int replacement, long int goal)
{
	char tmp[50];
	
	sprintf(tmp, "%d-%d-%d-%d-%d-%ld.txt", player, dealer, soft ? 1 : 0, decision, replacement, goal);
	
	char* filename = (char*) malloc(sizeof(char) * (strlen(tmp) + 1));
	sprintf(filename, "%s", tmp);
	filename[strlen(filename)] = '\0';
	
	return filename;
}

bool initParams(int argc, char* argv[], int* status, long int* goal, char* test)
{
	if (argc < 2)
	{
		puts("Too few parameters. Need at least 1 :");
		puts(" - status        int     -1 or 1");
		puts(" - [test]        int     H/S for Hard/Soft Standing Numbers (H default)");
		puts(" - [goal]        int     How many hands to be tested (smart default)");
		puts("");
		return false;
	}
	
	*status = atoi(argv[1]);
	*test = (argc > 2) ? argv[2][0] : 'H';
	*goal = (argc > 3) ? atol(argv[3]) : -1;
	
	return true;
}
/*
bool initParams(int argc, char* argv[], int* player, int* dealer, bool* soft, int* decision, int* replacement, long int* goal, char* filename)
{
	if (argc < 7)
	{
		  puts("Too few parameters. Need at least 6 :");
		  puts(" - player        int     Player's hard value");
		  puts(" - dealer        int     Dealer's value");
		  puts(" - soft          bool    Whether the hand needs to be soft (1: soft, 0: hard)");
		printf(" - decision      int     DRAW: %d, DOUBLE DOWN: %d, SPLIT: %d\n", DRAW, DOUBLEDOWN, SPLIT);
		  puts(" - replacement   bool    Value that will be replaced in the table (see pdf)");
		  puts(" - goal          int     How many hands to be tested");
		  puts(" - [filename]    string  Log file that will be used (in output/)");
		puts("");
		return false;
	}
	
	*player = atoi(argv[1]);
	*dealer = atoi(argv[2]);
	*soft = atoi(argv[3]) == 1;
	*decision = atoi(argv[4]);
	*replacement = atoi(argv[5]);
	*goal = atoi(argv[6]);
	
	if (argc >= 8)
	{
		sprintf(filename, "%s", argv[7]);
	}
	else
	{
		sprintf(filename, "%s", generateFileName(*player, *dealer, *soft, *decision, *replacement, *goal));
	}
	
	DIR* output = opendir("output");
	if (output)
	{
		closedir(output);
	}
	else
	{
		system("mkdir output");
	}
	
	return true;
}
*/
char* truncate(char* str, int length)
{
	int i = 0;
	char* result = (char*) malloc(length * sizeof(char) + 1);
	for (i = 0 ; i < length && i < strlen(str) ; i++)
	{
		result[i] = str[i];
	}
	if (i == length && i < strlen(str))
	{
		result[i-1] = '$';
	}
	result[length] = '\0';
	return result;
}
