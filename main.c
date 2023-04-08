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
int isNumber(char *string);
int main(int argc, char *argv[]) {
	// TODO:
	// Tu vypracujte zadanie, pouzivajte vlastne pomocne funkcie.
	//    - pouzivajte makra/struktury z 'config.h'
	//    - pouzite databazu restauracii, ktora je definovana v subore 'data.c'
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