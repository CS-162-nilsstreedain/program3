# Program 3 Makefile
CC = g++ -std=c++11
exe_file = application
$(exe_file): empty.o rope.o pit.o gold.o bats.o wumpus.o event.o room.o cave.o main.o
	$(CC) empty.o rope.o pit.o gold.o bats.o wumpus.o event.o room.o cave.o main.o -o $(exe_file)
empty.o: empty.cpp
	$(CC) -c empty.cpp
rope.o: rope.cpp
	$(CC) -c rope.cpp
pit.o: pit.cpp
	$(CC) -c pit.cpp
gold.o: gold.cpp
	$(CC) -c gold.cpp
bats.o: bats.cpp
	$(CC) -c bats.cpp
wumpus.o: wumpus.cpp
	$(CC) -c wumpus.cpp
event.o: event.cpp
	$(CC) -c event.cpp
room.o: room.cpp
	$(CC) -c room.cpp
cave.o: cave.cpp
	$(CC) -c cave.cpp
main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -f *.out *.o $(exe_file)
