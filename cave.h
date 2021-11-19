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
	int xpos;
	int ypos;
	
	Room* getRoom(int, int) const;
	Room* getRandomRoom() const;
	void addEventToRandRoom(Event*);
public:
	Cave(int);
	
	void printSeparator() const;
	void printEvents(Room*) const;
	void printUserPos() const;
	void print(bool) const;
};

#endif /* cave_h */
