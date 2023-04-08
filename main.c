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
	int opt;
	char* optstring = ":p:n";
	int pSet = FALSE, nSet = FALSE, errorState = FALSE;
	struct position userPos;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'p':
                pSet = TRUE;
				errorState = extractPosition(optarg, &userPos.x, &userPos.y);
				if (errorState == TRUE)
				{
					printf("E1\n");
					return 0;
				}
				
                break;
            case 'n':
                if (pSet == TRUE)
				{
					nSet =TRUE;
				}
                break;
            default: /* '?' alebo ':' */
                printf("Neplatny prepinac alebo chybajuci argument prepinaca\n");
                return 1;
        }
    }

	printf("-p set?: %d -n set?: %d\n", pSet, nSet);
	//printf("pozicia x %d y %d", userPos.x, userPos.y);
	return 0;
}
//return 1 ak nastala chybova sutuacia
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