CC=gcc
FLAGS= -Wall -g

all: graph

graph: main.o MyGraph.o MyQueue.o
		$(CC) $(FLAGS) -o graph main.o MyGraph.o MyQueue.o

main.o: main.c MyGraph.h MyQueue.h
		$(CC) $(FLAGS) -c main.c

MyGraph.o: MyGraph.c MyGraph.h
		$(CC) $(FLAGS) -c MyGraph.c

MyQueue.o: MyQueue.c MyQueue.h MyGraph.h
		$(CC) $(FLAGS) -c MyQueue.c


.PHONY: clean all
#make clean
clean:
	rm -f *.o graph
