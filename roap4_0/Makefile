PROJECT_NAME = roap #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c99 -g

OBJECTS = main.o input.o output.o game_mode.o djisktra.o heap.o adjacencyList.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c structures.h adjacencyList.h
input.o: input.c input.h
output.o: output.c output.h
game_mode.o: game_mode.c game_mode.h
djisktra.o: djisktra.c djisktra.h input.h game_mode.h
heap.o: heap.c heap.h 
adjacencyList.o : adjacencyList.c adjacencyList.h

FILES_1=$(shell ls ../Bilhar_Pequeno/*.in)
FILES_2=$(shell ls ../Chess_Party/*.in)
FILES_3=$(shell ls ../Small/*.in)
FILES_4=$(shell ls ../Enunciado/*.in)

FILES_C1=$(shell ls ../Bilhar_Pequeno/*.sol)
FILES_C2=$(shell ls ../Chess_Party/*.sol)
FILES_C3=$(shell ls ../Small/*.sol)
FILES_C4=$(shell ls ../Enunciado/*.sol)

FILES=${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4}

FILES_C=${FILES_C1} ${FILES_C2} ${FILES_C3} ${FILES_C4}

test:
	for F in ${FILES}; do  ./roap $$F; done;

Bilhar_Pequeno:
	for F in ${FILES_1}; do  ./roap $$F; done;

Chess_Party:
	for F in ${FILES_2}; do  ./roap $$F; done;

Small:
	for F in ${FILES_3}; do  ./roap $$F; done;

Enunciado:
	for F in ${FILES_4}; do  ./roap $$F; done;

restore:
	git restore ${FILES_C}

clean:
	rm -f $(PROJECT_NAME) *.o
