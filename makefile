CC=gcc
FLAGS= -Wall -g

all: graph

graph: main.o graph.o queue.o
		$(CC) $(FLAGS) -o graph main.o graph.o queue.o

main.o: main.c MyGraph.h MyQueue.h
		$(CC) $(FLAGS) -c main.c

graph.o: MyGraph.c MyGraph.h
		$(CC) $(FLAGS) -c graph.c

queue.o: MyQueue.c MyQueue.h MyGraph.h
		$(CC) $(FLAGS) -c Queue.c


.PHONY: clean all
#make clean
clean:
	rm -f *.o graph
