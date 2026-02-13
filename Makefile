CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LDFLAGS=-mwindows
TARGET=postit_manager

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET) postits.txt

.PHONY: all clean