#include <stdio.h>
#include <stdlib.h>
#include "../headers/_variables.h"
#include "../headers/_config.h"
#include "../headers/functions.h"

extern bool FORCEDEBUG;

void printBars(char* str, bool centered)
{
	int i = 0, size = strlen(str);
	
	printf("| ");
	
	if (centered)
	{
		for (i = 0 ; i < (TERMINAL_SIZE_X-2-size)/2-1; i++)
		{
			printf(" ");
		}
	}
	
	printf("%s", str);
	for (i = size + 2 + (centered ? (TERMINAL_SIZE_X-2-size)/2-1 : 0) ; i < TERMINAL_SIZE_X - 1 ; i ++)
	{
		printf(" ");
	}
	printf("|\n");
}

void printBars(char* str)
{
	printBars(str, false);
}

void printHr(bool br)
{
	if (br)
	{
		puts("");
	}
	for (int i = 0 ; i < TERMINAL_SIZE_X ; i++)
	{
		printf("-");
	}
	puts("");
}

void printHr()
{
	printHr(false);
}

void printCardColor(char color)
{
	if (!LINUX)
	{
		printf("%c\n", color);
		return;
	}
	
	int icolor = 37;
	char command[50] = "";
	
	if (color == 'H')		icolor = 31;
	else if (color == 'S')	icolor = 34;
	else if (color == 'D')	icolor = 35;
	else if (color == 'C')	icolor = 32;
	
	sprintf(command, "printf '\\033[1;%d;40m'", icolor);
	system(command);
	printf("%c\n", color);
	system("printf '\\033[0m'");
}

void printColor(int color, char* str)
{
	if (!LINUX || !DEBUG_COLOR)
	{
		printf("%s", str);
		return;
	}
	
	char command[50] = "";
	
	sprintf(command, "printf '\\033[1;%d;40m'", color);
	system(command);
	printf("%s", str);
	system("printf '\\033[0m'");
}

void printMatrix(double** matrix, int y, int x)
{
	puts("");
	int i = 0, j = 0;
	for (i = 0 ; i < y ; i++)
	{
		printf("%d|", i);
		for (j = 0 ; j < x ; j ++)
		{
			if (matrix[i][j] > 0)
			printf("+");
			printf("%1.0f ", matrix[i][j]);
		}
		puts("");
	}
}

void printBlackJackTables(double** matrix, int y, int x, int plusy, bool simple, char subsitute)
{
	if (simple){}
	puts("");
	int i = 0, j = 0;

	printf("   ");
	for (j = 1 ; j < x ; j ++)
	{
		if ((j+1)%10 == 0)
		{
			printf("10 ");
		}
		else
		{
			printf(" %d ", (j+1) % 10);
		}
	}
	printf(" A ");
	puts("");
	printf("    ");
	for (j = 0 ; j < x ; j ++)
	{
		printf("-----");
	}
	puts("");

	for (i = y-1 ; i >= 0 ; i--)
	{
		if (subsitute == 'S')
		{
			if (i+plusy == 10) {
				printf("10|");
			}
			else if (i+plusy == 11) {
				printf("AA|");
			}
			else {
				printf("%d%d|", i+plusy, i+plusy);
			}
		}
		else
		{
			if (i+plusy < 10) {
				printf("%c", subsitute);
			}
			printf("%d|", i+plusy);
		}
		for (j = 1 ; j < x ; j ++)
		{
			if (matrix[i][j] < 0)
				printf("-1 ");
			else
				printf("   ");
			//printf("%1.0f ", matrix[i][j]);
		}
		if (matrix[i][0] < 0)
			printf("-1 ");
		else
			printf("   ");
		//printf("%1.0f ", matrix[i][0]);
		puts("");
	}
}

void printBlackJackTables(double** matrix, int y, int x, int plusy, bool simple)
{
	printBlackJackTables(matrix, y, x, plusy, simple, '0');
}

void printStatTable(int table[21][10], bool split)
{
	int i = 0, j = 0;
	
	printf("\n    ");
	for (j = 1 ; j <= 10 ; j++)
	{
		printf(" %d", (j+1) % 10);
	}
	printf("\n--------------------------\n");
	
	for (i = split ? 19 : 20 ; i >= 0 ; i -= split ? 2 : 1)
	{
		printf("%2d |", (i+1)/(split ? 2 : 1));
		for (j = 1 ; j <= 10 ; j++)
		{
			if (table[i][j % 10] != -1)
			{
				printf(" %d", table[i][j % 10]);
			}
			else
			{
				printf("  ");
			}
		}
		puts(" |");
	}
	printf("--------------------------\n    ");
	for (j = 1 ; j <= 10 ; j++)
	{
		printf(" %d", (j+1) % 10);
	}
	puts("\n");
}


void debug(char* str)
{
	if (!DEBUG && !FORCEDEBUG)
	{
		return;
	}
	
	printf("%s", str);
	
}

void debug(char* str, int color)
{
	if (!DEBUG && !FORCEDEBUG)
	{
		return;
	}
	
	if (color)
	{
		printColor(color, str);
	}
	else
	{
		printf("%s", str);
	}
}
