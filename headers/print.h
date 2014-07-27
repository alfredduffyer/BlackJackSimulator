#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "_config.h"
#include "functions.h"

#ifndef PRINT_H
#define PRINT_H

// Prints side bars
void printBars(char* str);

// Prints a horizontal bar
void printHr();

// Prints a card color with color
void printCardColor(char color);

// Prints a string with a color
void printColor(int color, char* str);

// Prints a matrix in a readable format
void printMatrix(double** matrix, int y, int x);

// Prints a BlackJack matrix
void printBlackJackTables(double** matrix, int y, int x, int plusy, bool simple, char subsitute);
void printBlackJackTables(double** matrix, int y, int x, int plusy, bool simple);	// subsitute='0'

// Prints a stats table
void printStatTable(int table[21][10], bool split);

#endif
