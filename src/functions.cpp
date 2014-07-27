#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/functions.h"
#include <time.h>
#include <sys/time.h>

int strlen(char* str)
{
	int i = 0;
	
	while (str[i++] != '\0');
	
	return i-1;
}

int random(int min, int max)
{
	int value = randomTemp(min, max);
	
	return value % (max - min + 1) + min;
}

int randomTemp(int min, int max)
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

long int getMilliTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (long int) (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
}

void spause()
{
	system("echo \"PAUSE\" && read a");
}




