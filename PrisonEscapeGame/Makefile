# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Target executable
TARGET = TheEscapeAwakens.exe

# Source files
SRCS = game.c item.c enemy.c player.c room.c commands.c

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean generated files
clean:
	rm -f $(TARGET)

# Rebuild everything
rebuild: clean all