#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "access_system.h"

// Funktion som skapar och initierar ett nytt accesssystem
AccessSystem* initSystem() {
    // Allokerar minne för själva systemet
    AccessSystem *system = (AccessSystem*)malloc(sizeof(AccessSystem));
    if (system == NULL) {
        // Om malloc misslyckas, skriv ut felmeddelande och avsluta
        fprintf(stderr, "ERROR: Failed to allocate memory for system\n");
        exit(1);
    }
    
    // Allokerar minne för kort-arrayen (startar med 10 platser)
    system->cards = (Card*)malloc(INITIAL_CAPACITY * sizeof(Card));
    if (system->cards == NULL) {
        // Om malloc misslyckas, frigör systemet och avsluta
        fprintf(stderr, "ERROR: Failed to allocate memory for cards\n");
        free(system);
        exit(1);
    }
    
    // Sätter startvärden
    system->count = 0; // Inga kort ännu
    system->capacity = INITIAL_CAPACITY; // Kan hålla 10 kort från början
    
    return system; // Returnerar det skapade systemet
}

// Funktion som frigör allt minne som systemet använder
void freeSystem(AccessSystem *system) {
    if (system != NULL) {
        // Frigör först kort-arrayen
        if (system->cards != NULL) {
            free(system->cards);
        }
        // Frigör sedan själva systemet
        free(system);
    }
}

// Funktion som letar efter ett specifikt kortnummer i systemet
int findCard(AccessSystem *system, int cardNumber) {
    // Loopar igenom alla kort
    for (int i = 0; i < system->count; i++) {
        // Om vi hittar kortnumret
        if (system->cards[i].cardNumber == cardNumber) {
            return i; // Returnera positionen (index) där kortet finns
        }
    }
    return -1; // Returnera -1 om kortet inte finns
}

// Funktion som utökar arrayens storlek när den blir full
void expandCapacity(AccessSystem *system) {
    // Dubblar kapaciteten (t.ex. från 10 till 20)
    int newCapacity = system->capacity * 2;
    
    // Försöker allokera om minnet med den nya storleken
    Card *newCards = (Card*)realloc(system->cards, newCapacity * sizeof(Card));
    
    if (newCards == NULL) {
        // Om realloc misslyckas
        fprintf(stderr, "ERROR: Failed to expand card storage\n");
        return;
    }
    
    // Uppdaterar systemet med den nya arrayen och kapaciteten
    system->cards = newCards;
    system->capacity = newCapacity;
}

// Funktion som lägger till ett nytt kort eller uppdaterar ett befintligt kort
void addOrUpdateCard(AccessSystem *system, int cardNumber, int hasAccess) {
    // Letar efter kortet i systemet
    int index = findCard(system, cardNumber);
    
    // Om kortet redan finns (index är inte -1)
    if (index != -1) {
        // Uppdatera kortets access och datum
        system->cards[index].hasAccess = hasAccess;
        system->cards[index].dateAdded = time(NULL); // Nuvarande tid
    } 
    // Om kortet inte finns, lägg till ett nytt kort
    else {
        // Om arrayen är full, utöka den först
        if (system->count >= system->capacity) {
            expandCapacity(system);
        }
        
        // Lägg till det nya kortet på nästa lediga plats
        system->cards[system->count].cardNumber = cardNumber;
        system->cards[system->count].hasAccess = hasAccess;
        system->cards[system->count].dateAdded = time(NULL); // Nuvarande tid
        system->count++; // Öka antalet kort med 1
    }
}

// Funktion som sparar alla kort till en fil (cards.txt)
void saveCardsToFile(AccessSystem *system) {
    // Öppnar filen för skrivning ("w" = write)
    FILE *file = fopen(CARDS_FILE, "w");
    if (file == NULL) {
        // Om filen inte kunde öppnas
        fprintf(stderr, "ERROR: Could not open file for writing\n");
        return;
    }
    
    // Skriv först antalet kort på första raden
    fprintf(file, "%d\n", system->count);
    
    // Loopar igenom alla kort och skriver dem till filen
    for (int i = 0; i < system->count; i++) {
        // Varje kort på en rad: kortnummer,access,datum
        fprintf(file, "%d,%d,%ld\n", 
                system->cards[i].cardNumber,
                system->cards[i].hasAccess,
                (long)system->cards[i].dateAdded);
    }
    
    fclose(file); // Stänger filen
    printf("\nSaved %d cards to file.\n", system->count);
}

// Funktion som laddar in kort från filen (cards.txt) när programmet startar
void loadCardsFromFile(AccessSystem *system) {
    // Öppnar filen för läsning ("r" = read)
    FILE *file = fopen(CARDS_FILE, "r");
    if (file == NULL) {
        // Om filen inte finns, börja med ett tomt system
        printf("\n\nNo saved cards found. Starting fresh.\n");
        return;
    }
    
    // Läser antalet sparade kort från första raden
    int savedCount;
    if (fscanf(file, "%d", &savedCount) != 1) {
        fclose(file);
        return;
    }
    
    // Om det inte finns några kort sparade
    if (savedCount <= 0) {
        fclose(file);
        return;
    }
    
    // Utökar arrayens kapacitet om den är för liten
    while (system->capacity < savedCount) {
        expandCapacity(system);
    }
    
    // Börjar räkna från 0
    system->count = 0;
    
    // Läser in alla kort från filen
    for (int i = 0; i < savedCount; i++) {
        int cardNumber, hasAccess;
        long timestamp;
        
        // Läser in ett kort (kortnummer,access,datum)
        if (fscanf(file, "%d,%d,%ld", &cardNumber, &hasAccess, &timestamp) == 3) {
            system->cards[i].cardNumber = cardNumber;
            system->cards[i].hasAccess = hasAccess;
            system->cards[i].dateAdded = (time_t)timestamp;
            system->count++; // Öka antalet kort
        } else {
            // Om något gick fel vid inläsning
            fprintf(stderr, "ERROR: Failed to read card %d from file\n", i + 1);
            break;
        }
    }
    
    fclose(file); // Stänger filen
    printf("Loaded %d cards from file.\n", system->count);
}
