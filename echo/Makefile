CC = gcc
CFLAGS = -Wall -std=c99
TARGET = echo
SOURCE = echo.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: all clean
