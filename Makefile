# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -std=c99

# Source files
SRC = $(wildcard src/*.c)

# Output executable name
TARGET = rayit_defense

# Raylib and system libraries
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Build target (no .o files saved)
$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean just removes the binary
clean:
	rm -f $(TARGET)
