#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "_config.h"
#include "functions.h"
#include "print.h"

void printBars(char* str)
{
	int i = 0, size = strlen(str);
	
	printf("| %s", str);
	
	for (i = size + 2 ; i < TERMINAL_SIZE_X - 1 ; i ++)
	{
		printf(" ");
	}
	
	printf("|\n");	
}

void printHr()
{
	int i = 0;
	for (i = 0 ; i < TERMINAL_SIZE_X ; i++)
	{
		printf("-");
	}
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

void printBlackJackTables(double** matrix, int y, int x, int plusy, char subsitute)
{
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
			printf("  %d  ", (j+1) % 10);
		}
	}
	printf(" A ");
	puts("");
	printf("  ");
	for (j = 0 ; j < x ; j ++)
	{
		printf("-----");
	}
	puts("");
	
	for (i = y-1 ; i >= 0 ; i--)
	{
		if (subsitute == 'S')
		{
			if (i+plusy == 10)
			{
				printf("10|");
			}
			else if (i+plusy == 11)
			{
				printf("AA|");
			}
			else
			{
				printf("%d%d|", i+plusy, i+plusy);
			}
		}
		else
		{
			if (i+plusy < 10)
			{
				printf("%c", subsitute);
			}
			printf("%d|", i+plusy);
		}
		for (j = 1 ; j < x ; j ++)
		{
			if (matrix[i][j] > 0)
			printf("+");
			printf("%1.1f ", matrix[i][j]);
		}
		if (matrix[i][0] > 0)
		printf("+");
		printf("%1.0f ", matrix[i][0]);
		puts("");
	}
}

void printBlackJackTables(double** matrix, int y, int x, int plusy)
{
	printBlackJackTables(matrix, y, x, plusy, '0');
}


