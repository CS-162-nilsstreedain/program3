/******************************************************
** Program: cave.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Cave class implementation file
** Input: N/A
** Output: N/A
******************************************************/

#include "cave.h"
#include "empty.h"
#include "rope.h"
#include "wumpus.h"
#include "pit.h"
#include "bats.h"
#include "gold.h"
#include <time.h>
#include <vector>

/*********************************************************************
 ** Function: Cave()
 ** Description: Constructor for the cave class
 ** Parameters: int size
 ** Pre-Conditions: size must be provided
 ** Post-Conditions: A cave of size size will be created and filled with the correct number of events
 *********************************************************************/
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
	
	// Sets local variables for the cave
	gameOver = false;
	wumpusAlive = true;
	goldCollected = false;
}

/*********************************************************************
 ** Function: ~Cave()
 ** Description: Destructor for the cave class
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The cave will be destructed.
 *********************************************************************/
Cave::~Cave() {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			delete getRoom(i, j);
}

/*********************************************************************
 ** Function: Cave()
 ** Description: Copy Constructor for the cave class
 ** Parameters: const Cave& cave
 ** Pre-Conditions: cave must be provided
 ** Post-Conditions: A copy of cave will be created
 *********************************************************************/
Cave::Cave(const Cave& cave) {
	size = cave.size;
	userX = cave.userX;
	userY = cave.userY;
	
	gameOver = cave.gameOver;
	wumpusAlive = cave.wumpusAlive;
	goldCollected = cave.goldCollected;
	
	for (int i = 0; i < size; i++) {
		std::vector<Room*> column;
 		for (int j = 0; j < size; j++)
			column.push_back(new Room(i, j, cave.getRoom(i, j)->getEvent()));
		this->cave.push_back(column);
	}
}

/*********************************************************************
 ** Function: Cave()
 ** Description: Assignment Operator Constructor for the cave class
 ** Parameters: const Cave& cave
 ** Pre-Conditions: cave must be provided
 ** Post-Conditions: A copy of cave will be created & returned
 *********************************************************************/
Cave& Cave::operator= (const Cave& cave) {
	size = cave.size;
	userX = cave.userX;
	userY = cave.userY;
	
	gameOver = cave.gameOver;
	wumpusAlive = cave.wumpusAlive;
	goldCollected = cave.goldCollected;
	
	for (int i = 0; i < size; i++) {
		std::vector<Room*> column;
		for (int j = 0; j < size; j++)
			column.push_back(cave.getRoom(i, j));
		this->cave.push_back(column);
	}
	
	return *this;
}

/*********************************************************************
 ** Function: getRoom()
 ** Description: Returns the Room at position (x, y)
 ** Parameters: int x, int y
 ** Pre-Conditions: x & y must be provided
 ** Post-Conditions: The room at (x, y) will be returned
 *********************************************************************/
Room* Cave::getRoom(int x, int y) const {
	return cave.at(x).at(y);
}

/*********************************************************************
 ** Function: isGameOver()
 ** Description: Returns the gameOver boolean
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The gameOver status will be returned
 *********************************************************************/
bool Cave::isGameOver() const {
	return gameOver;
}

/*********************************************************************
 ** Function: isWumpusAlive()
 ** Description: Returns the wumpusAlive boolean
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The wumpusAlive status will be returned
 *********************************************************************/
bool Cave::isWumpusAlive() const {
	return wumpusAlive;
}

/*********************************************************************
 ** Function: isGoldCollected()
 ** Description: Returns the goldCollected boolean
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The goldCollected status will be returned
 *********************************************************************/
bool Cave::isGoldCollected() const {
	return goldCollected;
}

/*********************************************************************
 ** Function: percept()
 ** Description: Prints the percept for the room at (x, y)
 ** Parameters: int x, int y
 ** Pre-Conditions: x & y must be provided
 ** Post-Conditions: The percept for the room at (x, y) will be printed
 *********************************************************************/
void Cave::percept(int x, int y) const {
	Event* event = getRoom(x, y)->getEvent();
	if (!(event->getId() == ' ') && !(event->getId() == 'r'))
		event->percept();
}

/*********************************************************************
 ** Function: percepts()
 ** Description: Prints percepts for rooms around the user's current room
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The percepts for a rooms around (x, y) will be printed
 *********************************************************************/
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

/*********************************************************************
 ** Function: setupRandomRoom()
 ** Description: Finds a random empt room and then adds a given event to it
 ** Parameters: Event *event
 ** Pre-Conditions: event must be provided
 ** Post-Conditions: A random empty room will be found and an event will be added ot it
 *********************************************************************/
void Cave::setupRandomRoom(Event *event) {
	bool emptyRoomFound = false;
	Room* randRoom;
	srand(time(0));
	
	// While an empty room has not been found
	while(!emptyRoomFound) {
		// Get a random room
		int randX = rand() % size;
		int randY = rand() % size;
		randRoom = getRoom(randX, randY);
		
		// Check if the room is empty
		emptyRoomFound = randRoom->getEvent()->getId() == ' ';
		
		// If it is empty, set the event. If the room is the rope, set the user position
		if (emptyRoomFound) {
			randRoom->setEvent(event);
			if (event->getId() == 'r') {
				userX = randX;
				userY = randY;
			}
		}
	}
}

/*********************************************************************
 ** Function: printSeparator()
 ** Description: Prints a separator between lines of the cave
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: A separator between lines of the cave will be printed.
 *********************************************************************/
void Cave::printSeparator() const {
	for (int i = 0; i < size; i++)
		std::cout << "+---";
	std::cout << "+" << std::endl;
}

/*********************************************************************
 ** Function: printEvents()
 ** Description: Prints the formatted event of a room to the command line
 ** Parameters: Room* room
 ** Pre-Conditions: room must be provided
 ** Post-Conditions: A formatted event of a room will be printedto the command line
 *********************************************************************/
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

/*********************************************************************
 ** Function: printUserPos()
 ** Description: Prints the formatted state of a room to the command line when the user is in that room
 ** Parameters: Room* room
 ** Pre-Conditions: room must be provided
 ** Post-Conditions: Prints the formatted state of a room to the command line when the user is in that room
 *********************************************************************/
void Cave::printUserPos(Room* room) const {
	std::cout << "| ";
	if (room->getXpos() == userX && room->getYpos() == userY)
		std::cout << "* ";
	else
		std::cout << "  ";
}

/*********************************************************************
 ** Function: print()
 ** Description: Prints the cave to the command line
 ** Parameters: bool debugMode
 ** Pre-Conditions: debugMode must be provided
 ** Post-Conditions: The cave will be printed to the command line
 *********************************************************************/
void Cave::print(bool debugMode) const {
	std::cout << "\x1B[2J\x1B[H";
	for (int i = 0; i < size; i++) {
		printSeparator();
		for (int j = 0; j < size; j++)
			if (debugMode)
				printEvents(getRoom(i, j));
			else
				printUserPos(getRoom(i, j));
		std::cout << "|" << std::endl;
	}
	printSeparator();
}

/*********************************************************************
 ** Function: moveUp()
 ** Description: Function for moving the player up a space on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The user will be moves if there is a space to move to
 *********************************************************************/
void Cave::moveUp() {
	if (userX > 0)
		userX--;
}

/*********************************************************************
 ** Function: moveDown()
 ** Description: Function for moving the player down a space on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The user will be moves if there is a space to move to
 *********************************************************************/
void Cave::moveDown() {
	if (userX < size - 1)
		userX++;
}

/*********************************************************************
 ** Function: moveLeft()
 ** Description: Function for moving the player left a space on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The user will be moves if there is a space to move to
 *********************************************************************/
void Cave::moveLeft() {
	if (userY > 0)
		userY--;
}

/*********************************************************************
 ** Function: moveRight()
 ** Description: Function for moving the player right a space on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The user will be moves if there is a space to move to
 *********************************************************************/
void Cave::moveRight() {
	if (userY < size - 1)
		userY++;
}

/*********************************************************************
 ** Function: arrowRoom()
 ** Description: Function for shooting an arrow into a room
 ** Parameters: int x, int y
 ** Pre-Conditions: x & y must be provided
 ** Post-Conditions: an arrow will be fired into the given room.
 *********************************************************************/
void Cave::arrowRoom(int x, int y) {
	if (x >= 0 && x < size && y >= 0 && y < size) {
		if (getRoom(x, y)->getEvent()->getId() == 'w') {
			getRoom(x, y)->setEvent(new Empty);
			wumpusAlive = false;
		}
	}
}

/*********************************************************************
 ** Function: arrowUp()
 ** Description: Function for shooting an arrow up a  on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An arrow will be fired in that direction on the map
 *********************************************************************/
void Cave::arrowUp() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX - i, userY);
}

/*********************************************************************
 ** Function: arrowDown()
 ** Description: Function for shooting an arrow down a  on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An arrow will be fired in that direction on the map
 *********************************************************************/
void Cave::arrowDown() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX + i, userY);
}

/*********************************************************************
 ** Function: arrowLeft()
 ** Description: Function for shooting an arrow left a  on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An arrow will be fired in that direction on the map
 *********************************************************************/
void Cave::arrowLeft() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX, userY - i);
	
}

/*********************************************************************
 ** Function: arrowRight()
 ** Description: Function for shooting an arrow right a  on the map
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An arrow will be fired in that direction on the map
 *********************************************************************/
void Cave::arrowRight() {
	for (int i = 1; i < 4; i++)
		arrowRoom(userX, userY + i);
	
}

/*********************************************************************
 ** Function: encounter()
 ** Description: Function for determining what to do whe the user enters a room with an event
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The event of the given room will be run.
 *********************************************************************/
void Cave::encounter() {
	switch (getRoom(userX, userY)->getEvent()->getId()) {
		case 'g':
			goldCollected = true;
			break;
		case 'w':
			std::cout << "You have been killed by the Wumpus!" << std::endl;
			gameOver = true;
			break;
		case 'p':
			std::cout << "You have fallen into the bottomless pit!" << std::endl;
			gameOver = true;
			break;
		case 'r':
			ropeEncounter();
			break;
		case 'b':
			batEncounter();
			break;
		default:
			break;
	}
}

/*********************************************************************
 ** Function: ropeEncounter()
 ** Description: Function for encountering a rope in the cave
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The game will end if the user collected the gold, otherwise it will continue
 *********************************************************************/
void Cave::ropeEncounter() {
	if (!goldCollected) {
		std::cout << "You may not leave the cave without the gold." << std::endl;
	} else {
		std::cout << "You have escpaed the cave with the gold!" << std::endl;
		gameOver = true;
	}
}

/*********************************************************************
 ** Function: batEncounter()
 ** Description: Function for encountering a bat in the cave
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The use will be teleported to a random room and the event for that room will be run.
 *********************************************************************/
void Cave::batEncounter() {
	std::cout << "You have been been moved to another room by a bat!" << std::endl;
	  srand(time(0));
	  userX = rand() % size;
	  userY = rand() % size;
	  encounter();
}
