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

// Prints a matrix in a readable format
void printMatrix(double** matrix, int y, int x);

// Prints a BlackJack matrix
void printBlackJackTables(double** matrix, int y, int x, int plusy, char subsitute);
void printBlackJackTables(double** matrix, int y, int x, int plusy);	// subsitute='0'

#endif
