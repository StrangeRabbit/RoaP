PROJECT_NAME = roap #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c99 -g #-O3

OBJECTS = main.o input.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c structures.h
input.o: input.c input.h

clean:
	rm -f $(PROJECT_NAME) *.o