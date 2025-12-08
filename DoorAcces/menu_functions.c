#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "access_system.h"
#include "SafeInput.h"

void displayMenu() {
    printf("\n======= ADMIN MENU =======\n");
    printf("1 Remote open door\n");
    printf("2 List all cards in system\n");
    printf("3 Add/remove access\n");
    printf("4 FAKE TEST SCAN CARD\n");
    printf("5 EXIT\n");
    printf("\nType in your choice: ");
}

// Funktion som visar lampans färg och väntar en viss tid
void showLamp(const char *color, int duration) {
    printf("CURRENTLY LAMP IS: %s\n", color);
    // Om duration är större än 0, vänta i så många sekunder
    if (duration > 0) {
        sleep(duration);
    }
}

// Funktion som öppnar dörren på distans (visar grön lampa i 3 sekunder)
void remoteOpenDoor() {
    printf("\n");
    showLamp("GREEN", 3); // Grön lampa = dörren är öppen
    printf("\n");
}

// Funktion som visar alla kort som finns i systemet
void listAllCards(AccessSystem *system) {
    printf("\n======== All cards in system ========\n\n");
    
    // Om det inte finns några kort i systemet
    if (system->count == 0) {
        printf("\n***No cards in system***\n");
        printf("\n\nPress 'ENTER' to continue\n");
        getchar(); // Väntar på att användaren trycker Enter
        return;
    }
    
    // Loopar igenom alla kort i systemet
    for (int i = 0; i < system->count; i++) {
        // Skapar en sträng för datumet
        char dateStr[26];
        // Konverterar tiden till ett läsbart format
        struct tm *timeInfo = localtime(&system->cards[i].dateAdded);
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", timeInfo);
        
        // Skriver ut kortnummer, om det har access, och när det lades till
        printf("Card: %-8d | Access: %-3s | Added: %s\n", 
               system->cards[i].cardNumber,
               system->cards[i].hasAccess ? "Yes" : "No", // Om hasAccess är 1 = "Yes", annars "No"
               dateStr);
    }
    printf("\nPress 'ENTER' to continue . . . \n");
    getchar(); // Väntar på att användaren trycker Enter
    printf("\n");
}

// Funktion för att lägga till eller ta bort access för ett kort
void addRemoveAccess(AccessSystem *system) {
    printf("\n");
    printf("\nNOTE: Card numbers should not start with '0' (leading zeros will be removed)\n");
    
    // Frågar användaren efter kortnummer
    int cardNumber = readInt("\nEnter cardnumber ---> ");
    
    // Letar efter kortet i systemet
    int index = findCard(system, cardNumber);
    
    // Om kortet finns (index är inte -1)
    if (index != -1) {
        printf("This card has %s", 
               system->cards[index].hasAccess ? "ACCESS" : "NO ACCESS");
    } else {
        // Om kortet inte finns, kommer ett nytt kort skapas
        printf("Card %d not found in system. A new card will be created.", cardNumber);
    }
    
    // Frågar om användaren vill ge eller neka access
    int choice = readInt("\n\nCHOOSE ACCESS; \n\n1 GRANT ACCESS \n2 DENY ACCESS\n");
    
    // Om valet är 1, ge access
    if (choice == 1) {
        addOrUpdateCard(system, cardNumber, 1); // 1 = har access
        saveCardsToFile(system); // Sparar ändringarna till filen
        printf("\nCard %d has been * GRANTED ACCESS *\n", cardNumber);
    } 
    // Om valet är 2, neka access
    else if (choice == 2) {
        addOrUpdateCard(system, cardNumber, 0); // 0 = ingen access
        saveCardsToFile(system); // Sparar ändringarna till filen
        printf("\nCard %d has been * DENIED ACCESS *\n", cardNumber);
    } 
    // Om valet är varken 1 eller 2
    else {
        printf("\nInvalid choice.\n");
    }
    printf("\n");
}

// Funktion som simulerar kortskanning (för att testa systemet)
void fakeCardScanning(AccessSystem *system) {
    char input[100]; // Array för att lagra användarens input
    
    printf("\nNOTE: Card numbers should not start with '0' (leading zeros will be removed)\n");
    
    // Loop som fortsätter tills användaren skriver "X"
    while (1) {
        printf("\n***Please scan card to enter or X to go back to the main menu***\n");
        showLamp("OFF", 0); // Visar att lampan är av
        printf("\nEnter cardnumber ---> ");
        
        // Läser in användarens input (kortnummer eller X)
        readString("", input, sizeof(input));
        
        // Om användaren skrev X eller x, gå tillbaka till menyn
        if (strcmp(input, "X") == 0 || strcmp(input, "x") == 0) {
            break; // Avsluta loopen
        }
        
        // Försöker konvertera input till ett nummer
        int cardNumber;
        if (sscanf(input, "%d", &cardNumber) != 1) {
            printf("Invalid input\n");
            continue; // Hoppa över resten och börja om loopen
        }
        
        // Letar efter kortet i systemet
        int index = findCard(system, cardNumber);
        
        // Om kortet finns OCH har access
        if (index != -1 && system->cards[index].hasAccess) {
            showLamp("GREEN", 2); // Grön lampa = access godkänd
        } 
        // Om kortet inte finns ELLER inte har access
        else {
            showLamp("RED", 2); // Röd lampa = access nekad
        }
    }
    printf("\n");
}
