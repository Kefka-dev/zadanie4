// Pomocou #include pripojte do 
// programu hlavickovy subor 'config.h'.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "config.h"

#define TRUE 1
#define FALSE 0
#define POS_DELIM ","
int extractPosition(char* positionString, int* posX, int* posY);
int isNumber(char *string);
int main(int argc, char *argv[]) {
	// TODO:
	// Tu vypracujte zadanie, pouzivajte vlastne pomocne funkcie.
	//    - pouzivajte makra/struktury z 'config.h'
	//    - pouzite databazu restauracii, ktora je definovana v subore 'data.c'
int extractPosition(char* positionString, int* posX, int* posY){
	// sscanf(positionString, "%d,%d", posX, posY);
	char *token1, *token2;
	//int isNumber;
	token1 = strtok(positionString, POS_DELIM);
	// printf("token %s\n", token1);
	token2 = strtok(NULL, POS_DELIM);
	// printf("druhy token %s\n", token2);
	if(token1 == NULL || token2 == NULL)
	{
		return 1;
	}
	
	if (isNumber(token1) == FALSE || isNumber(token2) == FALSE)
	{
		return 1;
	}
	

	
	return 0;
}
//return 1 ak je string cislo, inac 0
int isNumber(char *string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if(isdigit(string[i]) == FALSE)
		{
			return 0;
		}
	}
	return 1;
}