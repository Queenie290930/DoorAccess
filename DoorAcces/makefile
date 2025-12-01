# Compiler och flaggor
CC       := clang
CFLAGS   := -Wall -Wextra -std=c17

# Namn på körbar fil
TARGET   := access_system

# Källfiler (*.c) och objektfiler (*.o)
SRCS     := main.c SafeInput.c card_manager.c menu_functions.c
OBJS     := $(SRCS:.c=.o)

# Standard‐mål
all: $(TARGET)

# Länkning: gör körbar fil från objektfiler
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Kompilering: .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rensa upp
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
