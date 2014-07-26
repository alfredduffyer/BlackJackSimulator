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

void addToFile(char* fileName, char* str)
{
	FILE* fichier = NULL;
	char filePath[50];
	
	sprintf(filePath, "output/%s", fileName);
	
	fichier = fopen(filePath, "a+");
	
	fprintf(fichier, "%s", str);
	
	fclose(fichier);
}
