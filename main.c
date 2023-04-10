// Pomocou #include pripojte do 
// programu hlavickovy subor 'config.h'.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "config.h"

#define TRUE 1
#define FALSE 0
#define POS_DELIM ","

typedef struct vyhodnostJedla {
	int CV;
	int Dm;
	int indexRestDB;
	int indexJedloMenu;
	int best;
} VYHODNOSTJEDLA;

int extractPosition(char* positionString, int* posX, int* posY);
int isNumber(char *string);
int wantedFoodRestaurant(	char* wantedFood,
							struct position userPos,
							VYHODNOSTJEDLA *najdeneJedla,
							int najdeneJedlaSize);
int compareCV(const void *a, const void *b);
int minCV(struct vyhodnostJedla *najdeneJedla, int najdeneJedlaSize);

int main(int argc, char *argv[]) {
	int opt;
	char* optstring = ":p:n";
	int pSet = FALSE, nSet = FALSE, errorState = FALSE;
	struct position userPos;
	char wantedFood[MAX_NAME+1];
	int jedloCount;
	VYHODNOSTJEDLA najdeneJedla[DB_NUM];
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
				fgets(wantedFood, MAX_NAME+1, stdin);
				wantedFood[strlen(wantedFood)-1] = '\0';
				//printf("%s", wantedFood);
				jedloCount = wantedFoodRestaurant(wantedFood, userPos, najdeneJedla, DB_NUM);
				
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
	if (optind == argc)
	{
		//vypis vsetkych restauracii
		for (int i = 0; i < DB_NUM; i++)
		{
			printf("%s\n%d,%d\n%d\n", db[i].name, db[i].pos.x, db[i].pos.y, db[i].n);
			for (int j = 0; j < db[i].n; j++)
			{
				printf("%d. %s,%d\n", j+1, db[i].menu[j].name, db[i].menu[j].price);
			}
			printf("\n");
		}
		
		return 0;
	}
	
	printf("-p set?: %d -n set?: %d\n", pSet, nSet);
	printf("pozicia x %d y %d\n", userPos.x, userPos.y);
	return 0;
}
//return 1 ak nastala chybova sutuacia
int extractPosition(char* positionString, int* posX, int* posY){
	char *token1, *token2;
	token1 = strtok(positionString, POS_DELIM);
	token2 = strtok(NULL, POS_DELIM);

	if(token1 == NULL || token2 == NULL)
	{
		return 1;
	}
	
	if (isNumber(token1) == FALSE || isNumber(token2) == FALSE)
	{
		return 1;
	}
	
	sscanf(token1, "%d", posX);
	sscanf(token2, "%d", posY);
	
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

//najde jedla, do pola ulozi CV, indexjedla, index Restiky a vrati pocet najdenych jedal
int wantedFoodRestaurant(char* wantedFood, struct position userPos, VYHODNOSTJEDLA *najdeneJedla, int najdeneJedlaSize)
{
	//printf("test");
	int CV = 0;
	int Dm = 0;
	int jedloCount = 0;
	for (int i = 0; i < DB_NUM; i++)
	{
		for (int j = 0; j < db[i].n; j++)
		{
			Dm = abs(userPos.x - db[i].pos.x) + abs(userPos.y -db[i].pos.y);
			if (strcmp(wantedFood, db[i].menu[j].name) == 0)
			{
				if (jedloCount < najdeneJedlaSize)
				{
					najdeneJedla[jedloCount].CV = 10*Dm + 100*db[i].menu[j].price;
					najdeneJedla[jedloCount].Dm = Dm;
					najdeneJedla[jedloCount].indexRestDB = i;
					najdeneJedla[jedloCount].indexJedloMenu = j;
					jedloCount++;
				}
				
				//printf("jedlo v restike cislo %d cenova vyhodnost %d\n", i, CV);
				
			}
			
		}
		
	}
	return jedloCount;
}

//qsort potrebuje compare funkciu ktorej da 2 void pointre a vrati int
int compareCV(const void *a, const void *b)
{
	const struct vyhodnostJedla *jedloA = (const struct vyhodnostJedla *)a;
	const struct vyhodnostJedla *jedloB = (const struct vyhodnostJedla *)b;
	
	if (jedloA->CV < jedloB->CV)
	{
		return -1;
	} else if ( jedloA->CV < jedloB->CV) 
	{
		return 1;
	} else 
	{
		return 0;
	}
	
}

int minCV(struct vyhodnostJedla *najdeneJedla, int najdeneJedlaSize)
{
	int najmensieCV = najdeneJedla[0].CV;
	for (int i = 1; i < najdeneJedlaSize; i++)
	{
		if (najdeneJedla[i].CV<najmensieCV)
		{
			najmensieCV = najdeneJedla[i].CV;
		}
	}
	
	for (int i = 0; i < najdeneJedlaSize; i++)
	{
		if (najdeneJedla[i].CV == najmensieCV)
		{
			najdeneJedla[i].best = TRUE;
		}
		else
		{
			najdeneJedla[i].best = FALSE;
		}
		
	}
	return 0;
}