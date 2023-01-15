# Macros ------------------------------------------------

CC=gcc # for c
AR=ar # for static libraries 
MAIN=main.o
FLAGS=-Wall

# Targets -----------------------------------------------

all: graph

graph: main.o graph.o algs.o
	$(CC) -g $(FLAGS) -o graph main.o graph.o algs.o -lm

main.o: main.c graph.h
	$(CC) -g $(FLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) -g  $(FLAGS) -c graph.c

algs.o: algs.c algs.h
	$(CC) -g $(FLAGS) -c algs.c

.PHONY: clean all

clean:
	rm -f *.a *.o  graph