CC=gcc
FLAGS = -Wall -g
OBJECTS=main.o graph.o algo.o

all: graph

graph: $(OBJECTS)
	$(CC) $(FLAGS) -o graph $(OBJECTS)
	
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

algo.o: algo.c graph.h
	$(CC) $(FLAGS) -c algo.c

.PHONY: clean all

clean:
	rm -f *.o graph
