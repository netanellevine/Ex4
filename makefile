all: graph

graph: main.c Queue.c graph.c graph.h Queue.h
	gcc -Wall -o graph main.c Queue.c graph.c
.PHONY: clean all

clean:
	rm -f graph
