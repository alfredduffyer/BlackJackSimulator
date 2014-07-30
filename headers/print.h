#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"
#include "functions.h"

#ifndef PRINT_H
#define PRINT_H

// Prints side bars according to the console size
void printBars(char* str);

// Prints a horizontal bar according to the console size
void printHr();

// Prints a card with a color accoring to the actual card's color
void printCardColor(char color);

// Prints a string with a color
void printColor(int color, char* str);

// Prints a matrix in a readable format
void printMatrix(double** matrix, int y, int x);

// Prints a BlackJack matrix
void printBlackJackTables(double** matrix, int y, int x, int plusy, bool simple, char subsitute);

// Prints a BlackJack matrix with the default paramter (substitute = '0')
void printBlackJackTables(double** matrix, int y, int x, int plusy, bool simple);

// Prints a stats table
void printStatTable(int table[21][10], bool split);

#endif
