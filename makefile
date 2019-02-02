#Adapted from the tutorial "How to Create a Simple Makefile - Introduction to Makefiles"
#https://www.youtube.com/watch?v=_r7i5X0rXJk
#and "A Simple Makefile Tutorial"
#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC = g++
CFLAGS = -g -std=c++11
OBJ = main.o Menu.o Board.o Critter.o Doodlebug.o Ant.o

output: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

main.o: main.cpp
	$(CC) -c $(CFLAGS) $^

Menu.o: Menu.cpp
	$(CC) -c $(CFLAGS) $^

Board.o: Board.cpp
	$(CC) -c $(CFLAGS) $^

Critter.o: Critter.cpp
	$(CC) -c $(CFLAGS) $^

Doodlebug.o: Doodlebug.cpp
	$(CC) -c $(CFLAGS) $^

Ant.o: Ant.cpp
	$(CC) -c $(CFLAGS) $^

clean:
	rm -f core $(OBJ) *~ output
