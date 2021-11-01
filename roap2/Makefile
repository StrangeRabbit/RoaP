# AED 2019-2020, sem.2
# Makefile for Lab5 graphs
# Last edit: abl 2020.04.21
#-----------------------------------------------------------------------
#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall

#   Sources

SOURCES = LinkedList.c  main.c

#   Objects  ('Make' automatically compiles .c to .o)

OBJECTS = LinkedList.o main.o

all: ola

ola: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

LinkedList.o: LinkedList.h defs.h LinkedList.c


clean::
	rm -f *.o core a.out pg1 pg2 listest  *~

VAL = valgrind --leak-check=full
# TRASH
#======================
# quick check of List package
listest: LinkedList.o listest.c
	$(CC) $(CFLAGS) -o $@ listest.c LinkedList.o

# tests w/ stdout dump to .edge | tail +3
tv:
	${VAL} ./pg1 ../AED_Lab_06-tests/grafo11.adj > grafo11.edge
	${VAL} ./pg1 ../AED_Lab_06-tests/grafo4.adj > grafo4.edge
	${VAL} ./pg1 ../AED_Lab_06-tests/grafo5.adj > grafo5.edge
	${VAL} ./pg1 ../AED_Lab_06-tests/grafo6.adj > grafo6.edge
t:
	./pg1 ../AED_Lab_06-tests/grafo11.adj > grafo11.edge
	./pg1 ../AED_Lab_06-tests/grafo4.adj > grafo4.edge
	./pg1 ../AED_Lab_06-tests/grafo5.adj > grafo5.edge
	./pg1 ../AED_Lab_06-tests/grafo6.adj > grafo6.edge
t2:
	./pg2 ../AED_Lab_06-tests/grafo11.edge
	./pg2 ../AED_Lab_06-tests/grafo4.edge
	./pg2 ../AED_Lab_06-tests/grafo5.edge
	./pg2 ../AED_Lab_06-tests/grafo6.edge
t2v:
	${VAL} ./pg2 ../AED_Lab_06-tests/grafo11.edge
	${VAL} ./pg2 ../AED_Lab_06-tests/grafo4.edge
	${VAL} ./pg2 ../AED_Lab_06-tests/grafo5.edge
	${VAL} ./pg2 ../AED_Lab_06-tests/grafo6.edge
