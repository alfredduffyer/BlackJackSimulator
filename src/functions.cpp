#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/functions.h"
#include <time.h>

int strlen(char* str)
{
	int i = 0;
	
	while (str[i++] != '\0');
	
	return i-1;
}

int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
