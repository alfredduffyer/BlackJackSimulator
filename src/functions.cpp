#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int strlen(char* str)
{
	int i = 0;
	
	while (str[i++] != '\0');
	
	return i-1;
}

bool strcmp(char* str1, char* str2)
{
	for (int i = 0 ; i < strlen(str1) && i < strlen(str2) ; i++)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}
	
	return true;
}

void sleep(int seconds)
{
	char command[15];
	sprintf(command, "sleep %d", seconds);
	system(command);
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




