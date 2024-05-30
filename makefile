CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -Llib
LDLIBS = -llua54 -lraylib -lopengl32 -lgdi32 -lwinmm

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = game.exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
