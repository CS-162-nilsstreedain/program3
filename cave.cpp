//
//  cave.cpp
//  Program 3
//
//  Created by Nils Streedain on 11/18/21.
//

#include "cave.h"
#include "rope.h"
#include "wumpus.h"
#include "pit.h"
#include "bats.h"
#include "gold.h"
#include <time.h>

Cave::Cave(int size) {
	this->size = size;
	// Fill 2D vector matrix of size by size with empty rooms
	for (int i = 0; i < size; i++) {
		// Create/Fill a 1D vector for each column of the matrix
		std::vector<Room*> column;
		for (int j = 0; j < size; j++)
			column.push_back(new Room);
		
		// Push each column to the matrix
		cave.push_back(column);
	}
	
	// Add all the required events to the cave rooms.
	addEventToRandRoom(new Rope);
	addEventToRandRoom(new Wumpus);
	addEventToRandRoom(new Pit);
	addEventToRandRoom(new Pit);
	addEventToRandRoom(new Bats);
	addEventToRandRoom(new Bats);
	addEventToRandRoom(new Gold);
}

Room* Cave::getRoom(int x, int y) const {
	return cave.at(x).at(y);
}


Room* Cave::getRandomRoom() const {
	srand(time(NULL));
	return getRoom(rand() % size, rand() % size);
}

void Cave::addEventToRandRoom(Event *event) {
	bool eventAdded = false;
	
	while(!eventAdded) {
		Room* randRoom = getRandomRoom();
		if (randRoom->getEvent() == nullptr) {
			randRoom->setEvent(event);
			eventAdded = true;
		}
	}
}

void Cave::printSeparator() const {
	for (int i = 0; i < size; i++)
		std::cout << "+---";
	std::cout << "+" << std::endl;
}

void Cave::printEvents(Room* room) const {
	Event* event = room->getEvent();
	std::cout << "| ";
	if (event == nullptr)
		std::cout << "  ";
	else
		std::cout << event->getId() << " ";
}

void Cave::printUserPos() const {
	// Placeholder code:
	std::cout << "|   ";
}

void Cave::print(bool debugMode) const {
	for (std::vector column : cave) {
		printSeparator();
		for (Room* room : column)
			if (debugMode)
				printEvents(room);
			else
				printUserPos();
		std::cout << "|" << std::endl;
	}
	printSeparator();
}
