CC=gcc
FLAGS= -Wall -g

all: graph

graph: main.o graph.o queue.o
		$(CC) $(FLAGS) -o graph main.o graph.o queue.o

main.o: main.c graph.h Queue.h
		$(CC) $(FLAGS) -c main.c

graph.o: graph.c graph.h
		$(CC) $(FLAGS) -c graph.c

queue.o: Queue.c Queue.h graph.h
		$(CC) $(FLAGS) -c Queue.c


.PHONY: clean all
#make clean
clean:
	rm -f *.o graph