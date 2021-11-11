PROJECT_NAME = roap #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c99 -g

OBJECTS = main.o reader.o queue.o lib.o bfs.o list.o djikstra.o heap.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c reader.h queue.h lib.h bfs.h list.h djikstra.h
bfs.o: bfs.c bfs.h queue.h lib.h
djikstra.o: djikstra.c djikstra.h heap.h
heap.o: heap.c heap.h
lib.o: lib.c lib.h
list.o: list.c list.h queue.h lib.h
queue.o: queue.c queue.h
reader.o: reader.c reader.h lib.h queue.h

FILES_1=$(shell ls Bilhar_Pequeno/*.in)
FILES_2=$(shell ls Chess_Party/*.in)
FILES_3=$(shell ls Small/*.in)
FILES_4=$(shell ls Enunciado/*.in)

FILES_C1=$(shell ls Bilhar_Pequeno/*.sol)
FILES_C2=$(shell ls Chess_Party/*.sol)
FILES_C3=$(shell ls Small/*.sol)
FILES_C4=$(shell ls Enunciado/*.sol)

FILES=${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4}

FILES_C=${FILES_C1} ${FILES_C2} ${FILES_C3} ${FILES_C4}

VALG = valgrind --leak-check=full -s

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

val:
	for F in ${FILES_4}; do ${VALG} ./roap $${F} ; done;

clean:
	rm -f $(PROJECT_NAME) *.o
