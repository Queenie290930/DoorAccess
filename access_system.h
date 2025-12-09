#ifndef ACCESS_SYSTEM_H
#define ACCESS_SYSTEM_H

#include <time.h>

// Konstanter för systemet
#define INITIAL_CAPACITY 10      // Hur många kort systemet kan hålla från början
#define CARDS_FILE "cards.txt"   // Filnamn där korten sparas

// Struktur som representerar ett accesskort
typedef struct {
    int cardNumber;      // Kortets nummer
    int hasAccess;       // 1 = har access, 0 = ingen access
    time_t dateAdded;    // När kortet lades till (datum och tid)
} Card;

// Struktur som representerar hela accesssystemet
typedef struct {
    Card *cards;         // Pekare till en array av kort
    int count;           // Antal kort som finns just nu
    int capacity;        // Hur många kort arrayen kan hålla
} AccessSystem;

// Funktioner för att hantera systemet
AccessSystem* initSystem();                     // Skapar ett nytt system
void freeSystem(AccessSystem *system);          // Frigör minne när programmet stängs

// Funktioner för att hantera kort
int findCard(AccessSystem *system, int cardNumber);                          // Letar efter ett kort
void addOrUpdateCard(AccessSystem *system, int cardNumber, int hasAccess);   // Lägger till eller uppdaterar ett kort
void expandCapacity(AccessSystem *system);                                   // Utökar arrayens storlek

// Funktioner för att spara och ladda från fil
void saveCardsToFile(AccessSystem *system);     // Sparar alla kort till fil
void loadCardsFromFile(AccessSystem *system);   // Laddar kort från fil

// Funktioner för menyn och gränssnittet
void displayMenu();                             // Visar menyn
void showLamp(const char *color, int duration); // Visar lampans färg

// Funktioner för olika val i menyn
void remoteOpenDoor();                          // Öppnar dörren på distans
void listAllCards(AccessSystem *system);        // Visar alla kort
void addRemoveAccess(AccessSystem *system);     // Lägg till/ta bort access
void fakeCardScanning(AccessSystem *system);    // Simulerar kortskanning

#endif
