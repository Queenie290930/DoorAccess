#include <stdio.h>
// Inkluderar våra egna filer
#include "SafeInput.h"
#include "access_system.h"

// Huvudfunktionen - här startar programmet
int main() {
    printf("\n================================================================\n");
    
    AccessSystem *system = initSystem(); // skapar systemet
    loadCardsFromFile(system); // laddar kort från fil
    
    int running = 1;
    
    while (running) {
        // Visar menyn för användaren
        displayMenu();
        
        // Läser in användarens val
        int choice = readInt("");
        
        // Kollar vad användaren valde och kör rätt funktion
        switch (choice) {
            case 1:
                // Öppnar dörren på distans
                remoteOpenDoor();
                break;
            case 2:
                listAllCards(system); // visar alla kort
                break;
            case 3:
                // Lägger till eller tar bort access för ett kort
                addRemoveAccess(system);
                break;
            case 4:
                fakeCardScanning(system); // testa scanna kort
                break;
            case 5:
                // Sparar alla kort till fil och avslutar programmet
                saveCardsToFile(system);
                running = 0; // Sätter running till 0 så loopen slutar
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    
    // Frigör minnet som systemet använder innan programmet stängs
    freeSystem(system);
    return 0;
}
