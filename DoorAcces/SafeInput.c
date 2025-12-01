// Inkluderar nödvändiga filer
#include "SafeInput.h"
#include <stdio.h>
#include <string.h>

// Funktion som läser in text på ett säkert sätt
void safeInput(char *buffer, int maxSize) {
    // Läser in text från användaren
    if (fgets(buffer, maxSize, stdin) != NULL) {
        size_t len = strlen(buffer);
        
        // Om texten slutar med Enter (\n), ta bort den
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; // Ersätt \n med \0 (slut på sträng)
        }
        
        // Om bufferten blev full, rensa resten av input
        if (len == (size_t)(maxSize - 1) && buffer[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Läs och kasta bort resten
        }
    }
}

// Funktion som läser in ett heltal (int) på ett säkert sätt
int readInt(const char *prompt) {
    char buffer[100];  // Tillfällig plats för texten
    int value;         // Det nummer vi vill få
    int validInput = 0; // 0 = inte giltigt ännu, 1 = giltigt
    
    // Fortsätt fråga tills användaren skriver ett giltigt nummer
    while (!validInput) {
        printf("%s", prompt); // Skriv ut frågan
        safeInput(buffer, sizeof(buffer)); // Läs in svaret
        
        // Försök konvertera texten till ett nummer
        if (sscanf(buffer, "%d", &value) == 1) {
            validInput = 1; // Det fungerade! Avsluta loopen
        } else {
            // Om det inte gick att konvertera till nummer
            printf("Invalid input. Please enter a number.\n");
        }
    }
    
    return value; // Returnera numret
}

// Funktion som läser in en textsträng på ett säkert sätt
void readString(const char *prompt, char *buffer, int maxSize) {
    printf("%s", prompt); // Skriv ut frågan
    safeInput(buffer, maxSize); // Läs in svaret
}
