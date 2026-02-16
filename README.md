# Door Access Control System
<img width="606" height="953" alt="Skärmavbild 2026-02-16 kl  19 29 03" src="https://github.com/user-attachments/assets/88011cb9-07f8-4097-97a1-cf2232130910" />


A C program for managing access cards to doors. School project in programming.

## What the program does

- Open door remotely
- Add and remove access cards
- Test card scanning
- Lamps show if access is granted (green) or denied (red)
- Saves all cards to a file

## How to run the program
```
DoorAccess/
├── main.c              # Main program entry and menu loop
├── card_manager.c      # Card data management and file operations
├── menu_functions.c    # User interface and menu functions
├── access_system.h     # System structures and function declarations
├── SafeInput.c         # Secure input handling functions
├── SafeInput.h         # Input function declarations
├── cards.txt           # Persistent card data storage
└── README.md           # This file
```

### System Design
- **No Global Variables**: All system state managed through `AccessSystem` struct
- **Modular Functions**: Each file handles specific responsibilities
- **Clean Interfaces**: Well-defined function signatures and data structures

## How to run the program

### Compile:
```bash
make
```

### Run:
```bash
./access_system
```

## Files in the project

```
DoorAccess/
├── main.c              # Main program with menu
├── card_manager.c      # Handles cards and file storage
├── menu_functions.c    # Menu functions
├── access_system.h     # Structures and declarations
├── SafeInput.c         # Safe input handling
├── SafeInput.h         # Header for SafeInput
├── cards.txt           # Cards are saved here
└── README.md           # This file
```

## Menu options

1. **Remote open door** - Opens the door manually
2. **List all cards** - Shows all cards
3. **Add/remove access** - Add or remove access
4. **Test Card Scanning** - Test scanning cards (type X to exit)
5. **Exit** - Save and quit

## Important to know

- Card numbers should NOT start with 0
- Cards are automatically saved in `cards.txt`
- 1 = has access, 0 = no access

## Technical info

### Structures used:
```c
typedef struct {
    int cardNumber;      // Card number
    int hasAccess;       // 1 = access, 0 = no access
    time_t dateAdded;    // When the card was added
} Card;

typedef struct {
    Card *cards;         // Array of cards
    int count;           // Number of cards
    int capacity;        // How many cards can fit
} AccessSystem;
```

### How memory is managed:
- Starts with space for 10 cards
- Automatically doubles when full (10→20→40→80...)
- Uses `malloc()` and `free()` to manage memory

## 📄 About

This is a school project for learning C programming, focusing on memory management, file handling, and secure input validation.

---

*Made as a learning exercise in C programming.*
