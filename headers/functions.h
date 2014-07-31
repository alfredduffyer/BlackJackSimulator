#ifndef FUNCTIONS
#define FUNCTIONS

// Gives the length of a string in characters
int strlen(char* str);

// Compares two strings (boolean version)
bool strcmp(char* str1, char* str2);

// Sleeps for a given number of seconds
void sleep(int seconds);

// Makes a pause in the program calling system(), waits until the user hits RETURN
void spause();

// Gives a good random number between min and max included
int random(int min, int max);

// Simplified log system : adds a string to the end of a file (in the output directory)
void addToFile(char* fileName, char* str);

// Gets the time in milliseconds
long int getMilliTime();

#endif
