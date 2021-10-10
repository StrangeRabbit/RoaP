PROJECT_NAME = roap #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c99 -O3

OBJECTS = main.o input.o output.o game_mode.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c structures.h
input.o: input.c input.h
output.o: output.c output.h
game_mode.o: game_mode.c game_mode.h

clean:
	rm -f $(PROJECT_NAME) *.o