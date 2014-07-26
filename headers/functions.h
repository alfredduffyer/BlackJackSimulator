#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "_config.h"

#ifndef FUNCTIONS
#define FUNCTIONS

// Gives the size of a string
int strlen(char* str);

// Gives a massively random number between min and max included
int random(int min, int max);

// Help for random number generator
int randomTemp(int min, int max);

// Adds a string to the end of a file
void addToFile(char* fileName, char* str);

// Gets the time in milliseconds
long int getMilliTime();


#endif
