/******************************************************
** Program: cave.h
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Cave object header file
** Input: N/A
** Output: N/A
******************************************************/

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
	
	void setupRandomRoom(Event*, int);
	Room* getRoom(int, int) const;
	void percept(int, int) const;
	void printSeparator() const;
	void printEvents(Room*) const;
	void printUserPos(Room*) const;
	
	void arrowRoom(int, int);
	void wumpusEncounter();
	void ropeEncounter();
	void batEncounter();
public:
	Cave(int, int);
	~Cave();
	
	bool isGameOver() const;
	bool isWumpusAlive() const;
	bool isGoldCollected() const;
	void percepts() const;
	void print(bool) const;
	void encounter();
	
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void arrowUp();
	void arrowDown();
	void arrowLeft();
	void arrowRight();
};

#endif /* cave_h */
