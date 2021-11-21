//
//  cave.cpp
//  Program 3
//
//  Created by Nils Streedain on 11/18/21.
//

#include "cave.h"
#include "empty.h"
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
			column.push_back(new Room(i, j));
		
		// Push each column to the matrix
		cave.push_back(column);
	}
	
	// Add all the required events to the cave rooms.
	setupRandomRoom(new Rope);
	setupRandomRoom(new Wumpus);
	setupRandomRoom(new Pit);
	setupRandomRoom(new Pit);
	setupRandomRoom(new Bats);
	setupRandomRoom(new Bats);
	setupRandomRoom(new Gold);
	
	gameOver = false;
	wumpusAlive = true;
	goldCollected = false;
}

Room* Cave::getRoom(int x, int y) const {
	return cave.at(x).at(y);
}

bool Cave::isGameOver() const {
	return gameOver;
}

bool Cave::isWumpusAlive() const {
	return wumpusAlive;
}

bool Cave::isGoldCollected() const {
	return goldCollected;
}

void Cave::percept(int x, int y) const {
	Event* event = getRoom(x, y)->getEvent();
	if (!(event->getId() == ' ') && !(event->getId() == 'r'))
		event->percept();
}

void Cave::percepts() const {
	if (userX < size - 1)
		percept(userX + 1, userY);
	if (userX > 0)
		percept(userX - 1, userY);
	if (userY < size - 1)
		percept(userX, userY + 1);
	if (userY > 0)
		percept(userX, userY - 1);
	std::cout << std::endl;
}

void Cave::setupRandomRoom(Event *event) {
	bool emptyRoomFound = false;
	Room* randRoom;
	srand(time(0));
	
	while(!emptyRoomFound) {
		int randX = rand() % size;
		int randY = rand() % size;
		randRoom = getRoom(randX, randY);
		emptyRoomFound = randRoom->getEvent()->getId() == ' ';
		
		if (emptyRoomFound) {
			randRoom->setEvent(event);
			if (event->getId() == 'r') {
				userX = randX;
				userY = randY;
			}
		}
	}
}

bool Cave::setupRoom(int Xpos, int Ypos, Event *event) {
	Room* randRoom = getRoom(Xpos, Ypos);
	bool roomIsEmpty = randRoom->getEvent() == nullptr;
	
	if (roomIsEmpty)
		randRoom->setEvent(event);
	
	return roomIsEmpty;
}

void Cave::printSeparator() const {
	for (int i = 0; i < size; i++)
		std::cout << "+---";
	std::cout << "+" << std::endl;
}

void Cave::printEvents(Room* room) const {
	Event* event = room->getEvent();
	std::cout << "| ";
	if (room->getXpos() == userX && room->getYpos() == userY)
		std::cout << "* ";
	else if (event == nullptr)
		std::cout << "  ";
	else
		std::cout << event->getId() << " ";
}

void Cave::printUserPos(Room* room) const {
	std::cout << "| ";
	if (room->getXpos() == userX && room->getYpos() == userY)
		std::cout << "* ";
	else
		std::cout << "  ";
}

void Cave::print(bool debugMode) const {
	std::cout << "\x1B[2J\x1B[H";
	for (std::vector column : cave) {
		printSeparator();
		for (Room* room : column)
			if (debugMode)
				printEvents(room);
			else
				printUserPos(room);
		std::cout << "|" << std::endl;
	}
	printSeparator();
}

void Cave::moveUp() {
	if (userX > 0)
		userX--;
}

void Cave::moveDown() {
	if (userX < size - 1)
		userX++;
}

void Cave::moveLeft() {
	if (userY > 0)
		userY--;
}

void Cave::moveRight() {
	if (userY < size - 1)
		userY++;
}

void Cave::arrowRoom(int x, int y) {
	if (x >= 0 && x < size && y >= 0 && y < size)
		if (getRoom(x, y)->getEvent()->getId() == 'w') {
			getRoom(x, y)->setEvent(new Empty);
			wumpusAlive = false;
		}
}

void Cave::arrowUp() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX - i, userY);
}

void Cave::arrowDown() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX + i, userY);
	
}

void Cave::arrowLeft() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX, userY - i);
	
}

void Cave::arrowRight() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX, userY + i);
	
}

void Cave::encounter() {
	switch (getRoom(userX, userY)->getEvent()->getId()) {
		case ' ':
			break;
		case 'w':
			std::cout << "You have been killed by the Wumpus!" << std::endl;
			gameOver = true;
			break;
		case 'p':
			std::cout << "You have fallen into the bottomless pit!" << std::endl;
			gameOver = true;
			break;
		case 'b':
			std::cout << "You have been been moved to another room by a bat!" << std::endl;
			srand(time(0));
			userX = rand() % size;
			userY = rand() % size;
			encounter();
			break;
		case 'g':
			goldCollected = true;
			break;
		case 'r':
			if (goldCollected) {
				std::cout << "You have escpaed the cave with the gold!" << std::endl;
				gameOver = true;
			} else
				std::cout << "You may not leave the cave without the gold." << std::endl;
			break;
		default:
			break;
	}
}
