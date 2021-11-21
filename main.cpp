//
//  main.cpp
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <ncurses.h>
#include "cave.h"

int verifySizeArgument(char *size) {
	// If size argument is left empty, an exception is thrown.
	if (size == NULL)
		throw std::invalid_argument("No size provided.");
	
	if (!(std::atoi(size) > 3))
		throw std::invalid_argument("Invalid size");
	
	return atoi(size);
}

bool verifyDebugArgument(char *debugMode) {
	// If debug argument is left empty, an exception is thrown.
	if (debugMode == NULL)
		throw std::invalid_argument("No debug mode provided.");
	
	// If debug argument is true, true is returned. If false, false is returned.
	if (!strcmp(debugMode, "true"))
		return true;
	else if (!strcmp(debugMode, "false"))
		return false;
	
	// If debug argument is anything else, an exception is thrown.
	throw std::invalid_argument("Invalid debug mode argument.");
}

char getUserInput(std::string inputMessage) {
	std::cout << inputMessage << std::endl;
	system("stty raw");
	char input = getchar();
	system("stty cooked");
	std::cout << std::endl;
	return input;
}

void fireArrow(Cave *cave) {
	switch (getUserInput("Press a key to fire an arrow: (W) North, (A) West, (S) South, (D) East")) {
		case 'w':
			cave->arrowUp();
			break;
		case 'a':
			cave->arrowLeft();
			break;
		case 's':
			cave->arrowDown();
			break;
		case 'd':
			cave->arrowRight();
			break;
		default:
			fireArrow(cave);
			break;
	}
}

int chooseMove(Cave *cave, int numArrows) {
	switch (getUserInput("Press a key to move: (W) Up, (A) Left, (S) Down, (D) Right, ( ) Fire Arrow")) {
		case 'w':
			cave->moveUp();
			break;
		case 'a':
			cave->moveLeft();
			break;
		case 's':
			cave->moveDown();
			break;
		case 'd':
			cave->moveRight();
			break;
		case ' ':
			if (numArrows > 0) {
				numArrows--;
				fireArrow(cave);
			}
			break;
		default:
			break;
	}
	return numArrows;
}

void printGameStatus(Cave *cave, int numArrows) {
	if (!cave->isWumpusAlive())
		std::cout << "You killed the Wumpus";
	else if (numArrows > 0)
		std::cout << "You have " << numArrows << " arrows left";
	if (cave->isGoldCollected())
		std::cout << " and have collected the gold!" << std::endl;
	else
		std::cout << " but have not collected the gold." << std::endl;
}

void newGame(Cave *cave, bool debugMode) {
	int numArrows = 3;
	Cave caveTemp = *cave;
	
	while (!caveTemp.isGameOver()) {
		// Print out user interface & have user choose move.
		caveTemp.print(debugMode);
		caveTemp.percepts();
		printGameStatus(&caveTemp, numArrows);
		numArrows = chooseMove(&caveTemp, numArrows);
		
		// Run encounter
		caveTemp.encounter();
	}
}

int main(int argc, const char * argv[]) {
	int size = verifySizeArgument((char*)argv[1]);
	bool debugMode = verifyDebugArgument((char*)argv[2]);
	
	Cave cave(size);
	newGame(&cave, debugMode);
	
	char input;
	do {
		input = getUserInput("Select Game: (1) Same Cave, (2) New Cave, (3) End Game");
		if (input == '1') {
			newGame(&cave, debugMode);
		} else if (input == '2') {
			cave = Cave(size);
			newGame(&cave, debugMode);
		}
	} while (input == '1' || input == '2');
	
    return 0;
}
