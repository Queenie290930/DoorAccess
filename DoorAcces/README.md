# Door Access Control System

A robust C-based access control system for managing card-based door entry. This system demonstrates secure programming practices, dynamic memory management, and persistent data storage.

## 📋 Features

### Core Functionality
- **Remote Door Control**: Admin can remotely open doors
- **Card Management**: Add, update, and remove card access permissions
- **Real-time Testing**: Simulate card scanning for testing purposes
- **Visual Feedback**: Color-coded lamp system (Red/Green/Off) for access status
- **Admin Interface**: Menu-driven system for easy administration

### Advanced Features
- **Persistent Storage**: Cards are automatically saved to file and restored on restart
- **Dynamic Memory Management**: Supports unlimited number of cards using automatic memory expansion
- **Input Validation**: Comprehensive protection against invalid input and buffer overflow attacks
- **Error Handling**: User-friendly error messages with graceful recovery
- **Modular Design**: Well-structured codebase with separation of concerns

## 🛡️ Security & Safety

### Buffer Overflow Protection
- Uses custom `SafeInput` library to prevent buffer overflow attacks
- All user input is validated and sanitized
- Safe string handling with proper bounds checking

### Memory Safety
- Proper memory allocation and deallocation
- Dynamic array expansion to handle unlimited cards
- No memory leaks through comprehensive cleanup

### Stack Safety
- No recursive function calls
- Controlled loop structures with proper exit conditions
- Prevents stack overflow scenarios

## 🏗️ Architecture

### File Structure
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

## 🚀 Getting Started

### Prerequisites
- GCC compiler
- Unix-like environment (macOS, Linux)
- Make utility

### Building the Project
```bash
make
```

### Running the System
```bash
./access_system
```

## 💡 Usage

### Admin Menu Options
1. **Remote Open Door** - Manually open the door (shows green lamp for 3 seconds)
2. **List All Cards** - Display all cards in the system with their access status
3. **Add/Remove Access** - Grant or deny access to specific card numbers
4. **Test Card Scanning** - Simulate card scanning at the door (type 'X' to exit)
5. **Exit** - Save data and quit the program

### Card Management
- Cards are identified by numeric IDs
- **Important**: Card numbers should not start with '0' (leading zeros will be removed)
- Each card has an access status (granted/denied)
- Cards are automatically timestamped when added or modified
- System auto-saves changes to prevent data loss

### File Format
Cards are stored in `cards.txt` with the format:
```
[number_of_cards]
[card_number],[access_status],[timestamp]
[card_number],[access_status],[timestamp]
...
```

## 🔧 Technical Implementation

### Data Structures
```c
typedef struct {
    int cardNumber;      // Unique card identifier
    int hasAccess;       // 1 = access granted, 0 = denied
    time_t dateAdded;    // Timestamp of last modification
} Card;

typedef struct {
    Card *cards;         // Dynamic array of cards
    int count;           // Current number of cards
    int capacity;        // Current array capacity
} AccessSystem;
```

### Memory Management
- Starts with initial capacity of 10 cards
- Automatically doubles capacity when full (10→20→40→80...)
- Uses `realloc()` for efficient memory expansion
- Proper cleanup prevents memory leaks

### Error Handling
- Comprehensive input validation
- User-friendly error messages
- Graceful degradation on errors
- File operation error handling

## 🧪 Testing

### Manual Testing
Use the "Test Card Scanning" feature (option 4) to simulate door access:
1. Enter card numbers to test access
2. Observe lamp colors (Green = access granted, Red = denied)
3. Type 'X' to return to `Admin Menu Options`

### Input Validation Testing
Try entering invalid data:
- Non-numeric input for card numbers
- Invalid menu choices
- Empty inputs

The system should handle all cases gracefully without crashing.

## 📝 Code Quality

### Best Practices Implemented
- **Clear Naming**: Descriptive function and variable names
- **Comprehensive Comments**: Explains both what and why
- **Error Handling**: Checks return values and handles failures
- **Resource Management**: Proper malloc/free pairing
- **Input Validation**: Prevents crashes from bad input
- **Modular Design**: Separation of concerns across files

### Safety Features
- No buffer overflows possible
- No stack overflows possible
- No global variables
- Safe input handling
- Robust error recovery

## 🔄 Data Persistence

The system automatically:
- **Saves** card data when changes are made
- **Loads** existing cards on startup
- **Creates** the data file if it doesn't exist
- **Handles** file operation errors gracefully

Cards persist between program runs, making this suitable for production use.


## 📄 License

This project is created for educational purposes, demonstrating secure C programming practices and system design principles.

---

*This access control system demonstrates professional level C programming with emphasis on security, reliability, and maintainability.*