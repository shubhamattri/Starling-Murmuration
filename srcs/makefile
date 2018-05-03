# $ make
# $ ./simulate-starling

CC = g++
CFLAGS = -c
DEBUG = -g
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: boids

boids: boidrules.o flockofboids.o vectorfunc.o main.o Simulation.o
	$(CC) $(DEBUG) boidrules.o flockofboids.o vectorfunc.o Simulation.o main.o -o simulate-starling $(SFML)

boidrules.o : boidrules.cpp
	$(CC) $(CFLAGS) $(DEBUG) boidrules.cpp

vectorfunc.o : vectorfunc.cpp
	$(CC) $(CFLAGS) $(DEBUG) vectorfunc.cpp

flockofboids.o : flockofboids.cpp
	$(CC) $(CFLAGS) $(DEBUG) flockofboids.cpp

Simulation.o : Simulation.cpp
	$(CC) $(CFLAGS) $(DEBUG) Simulation.cpp

clean:
	\rm *.o simulate-starling

tar:
	tar cfv boids.tar vectorfunc.h vectorfunc.cpp boidrules.h boidrules.cpp \
		flockofboids.h flockofboids.cpp Simulation.cpp Simulation.h
