/******************************************************
** Program: main.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Main driver file for hunt the wumpus.
** Input: Command Line Arguments to specify size & debug mode
** Output: The game will be output to the command line interface.
******************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <ncurses.h>
#include <string.h>
#include "cave.h"


/*********************************************************************
 ** Function: verifySizeArgument()
 ** Description: Function to make sure the command line argument for size is correct & then return it as an int.
 ** Parameters: char *size
 ** Pre-Conditions: size must be provided
 ** Post-Conditions: the size will be returned as an int if valid
 *********************************************************************/
int verifySizeArgument(char *size) {
	// If size argument is left empty, an exception is thrown.
	if (size == NULL)
		throw std::invalid_argument("No size provided.");
	
	// If the size is not a valid int or larger than 3, an exception is thrown.
	if (!(std::atoi(size) > 3))
		throw std::invalid_argument("Size must be larger than 3");
	
	return atoi(size);
}

/*********************************************************************
 ** Function: verifyDebugArgument()
 ** Description: Function to make sure the debug is correct & then return it as a bool.
 ** Parameters: char *debugMode
 ** Pre-Conditions: debugMode must be provided
 ** Post-Conditions: the debugMode will be returned as a bool iif valid
 *********************************************************************/
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

/*********************************************************************
 ** Function: getUserInput()
 ** Description: Fuction for getting a singly character input from the user without enter needing to be pressed.
 ** Parameters: std::string inputMessage
 ** Pre-Conditions: inputMessage may be provided
 ** Post-Conditions: the user input character will be returned
 *********************************************************************/
char getUserInput(std::string inputMessage) {
	std::cout << inputMessage << std::endl;
	
	// Sets command line input to retrieve a single char without enter being pressed
	system("stty raw");
	char input = getchar();
	system("stty cooked");
	
	std::cout << std::endl;
	return input;
}

/*********************************************************************
 ** Function: fireArrow()
 ** Description: Fuction to allow the user to select which direction to fire an arrow towards
 ** Parameters: Cave *cave
 ** Pre-Conditions: cave must be provided
 ** Post-Conditions: an arrow will be fired in the direction specified
 *********************************************************************/
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

/*********************************************************************
 ** Function: chooseMove()
 ** Description: Fuction to allow the user to select which move to make for the turn
 ** Parameters: Cave *cave, int numArrows
 ** Pre-Conditions: cave & numArrows must be provided
 ** Post-Conditions: the move will be made and if applicable, the number of arrows will be reduced and returned.
 *********************************************************************/
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

/*********************************************************************
 ** Function: printGameStatus()
 ** Description: Fuction to print the status of the wumpus, number of arrows left & the gold collection state
 ** Parameters: Cave *cave, int numArrows
 ** Pre-Conditions: cave & numArrows must be provided
 ** Post-Conditions: the function will print the state of the wumpus, number of arrows left & the gold collection state
 *********************************************************************/
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

/*********************************************************************
 ** Function: newGame()
 ** Description: Fuction start and manage a new game
 ** Parameters: Cave *cave, bool debugMode
 ** Pre-Conditions: cave & debugMode must be provided
 ** Post-Conditions: the function will start the game based on the cave & debug mode and return when the game hass ended
 *********************************************************************/
void newGame(int size, int seed, bool debugMode) {
	int numArrows = 3;
	Cave cave(size, seed);
	
	// While the game is not over, the game state will be printed and the user will be asked to make a move
	while (!cave.isGameOver()) {
		// Print out user interface & have user choose move.
		cave.print(debugMode);
		cave.percepts();
		printGameStatus(&cave, numArrows);
		numArrows = chooseMove(&cave, numArrows);
		
		// Run encounter
		cave.encounter();
	}
}

/*********************************************************************
 ** Function: main()
 ** Description: Main driver function for hunt the wumpus
 ** Parameters: command line arguments for size and debugMode
 ** Pre-Conditions: size & debugMode must be provided
 ** Post-Conditions: The function will create a cave and start a game, then ask the user what to do when the game has ended.
 *********************************************************************/
int main(int argc, const char * argv[]) {
	int size = verifySizeArgument((char*)argv[1]);
	bool debugMode = verifyDebugArgument((char*)argv[2]);
	srand(time(0));
	int seed = rand();
	
	// Creates a cave for the game to use
	// Starts a game based on that cave
	newGame(size, seed, debugMode);
	
	char input;
	do {
		// Gets user input on what to do when the game has ended.
		input = getUserInput("Select Game: (1) Same Cave, (2) New Cave, (3) End Game");
		
		// Determines what to do based on the input
		if (input == '1') {
			newGame(size, seed, debugMode);
		} else if (input == '2') {
			seed = rand();
			newGame(size, seed, debugMode);
		}
	} while (input == '1' || input == '2');
	
    return 0;
}
