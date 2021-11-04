PROJECT_NAME = roap #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c99 -g

OBJECTS = main.o input.o output.o game_mode.o djisktra.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c structures.h
input.o: input.c input.h
output.o: output.c output.h
game_mode.o: game_mode.c game_mode.h
djisktra.o: djisktra.c djisktra.h input.h game_mode.h

FILES_1=$(shell ls ../Bilhar_Pequeno/*.in)
FILES_2=$(shell ls ../Chess_Party/*.in)
FILES_3=$(shell ls ../Small/*.in)
FILES_4=$(shell ls ../Enunciado/*.in)


FILES=${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4}

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

clean:
	rm -f $(PROJECT_NAME) *.o