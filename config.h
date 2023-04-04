// MAKRA
#define MAX_NAME 100 // max. dlzka pre nazov jedla a restauracie
#define MAX_ITEMS 20 // max. pocet poloziek menu
#define DB_NUM 10 // pocet restauracii v databaze

// DATOVE TYPY

// Poloha na mape
typedef struct position {
    int x;
    int y;
} POSITION;

// Jedlo
typedef struct meal {
    char name[MAX_NAME + 1]; // nazov
    int price; // cena v EUR
} MEAL;

// Restauracia
typedef struct restaurant {
    char name[MAX_NAME + 1]; // nazov
    POSITION pos; // poloha
    int n; // aktualny pocet poloziek ponuky
    MEAL menu[MAX_ITEMS]; // databaza poloziek ponuky
} RESTAURANT;


// DEKLARACIE PREMENNYCH
extern RESTAURANT db[DB_NUM]; // databaza restauracii
