//
//  cave.h
//  Program 3
//
//  Created by Nils Streedain on 11/18/21.
//

#ifndef cave_h
#define cave_h

#include <iostream>
#include <vector>
#include "room.h"

class Cave {
private:
	int size;
	std::vector<std::vector<Room*>> cave;
	int userX;
	int userY;
	
	bool gameOver;
	bool wumpusAlive;
	bool goldCollected;
	
	void setupRandomRoom(Event*);
	bool setupRoom(int, int, Event*);
	
	void printSeparator() const;
	void printEvents(Room*) const;
	void printUserPos(Room*) const;
	void percept(int, int) const;
	
	void arrowRoom(int, int);
public:
	Cave(int);
	Room* getRoom(int, int) const;
	bool isGameOver() const;
	bool isWumpusAlive() const;
	bool isGoldCollected() const;
	void percepts() const;
	void print(bool) const;
	
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	
	void arrowUp();
	void arrowDown();
	void arrowLeft();
	void arrowRight();
	
	void encounter();
};

#endif /* cave_h */
