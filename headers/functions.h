#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"

#ifndef FUNCTIONS
#define FUNCTIONS

// Gives the length of a string in characters
int strlen(char* str);

// Gives a good random number between min and max included
int random(int min, int max);

// Simplified log system : adds a string to the end of a file (in the output directory)
void addToFile(char* fileName, char* str);

// Gets the time in milliseconds
long int getMilliTime();

// Makes a pause in the program calling system(), waits until the user hits RETURN
void spause();

#endif
