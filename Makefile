PROJECT_NAME = roap #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c99 -g #-O3

OBJECTS = main.o input.o output.o game_mode.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c structures.h
input.o: input.c input.h
output.o: output.c output.h
game_mode.o: game_mode.c game_mode.h

FILES_1=$(shell ls A1/*)
FILES_2=$(shell ls A2/*)
FILES_3=$(shell ls A3/*)
FILES_4=$(shell ls A4/*)
FILES_5=$(shell ls A5/*)
FILES_6=$(shell ls A6/*)
Saladas=$(shell ls Saladas/*)

FILES=${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4} ${FILES_5} ${FILES_6} ${Saladas}

test:
	for F in ${FILES}; do  ./roap -s $$F; done;

clean:
	rm -f $(PROJECT_NAME) *.o