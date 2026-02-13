CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LDFLAGS=-mwindows -lgdi32 -ldwmapi
TARGET=postit_manager
SOURCES=main.c postit.c gui.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) postits.txt

.PHONY: all clean