/******************************************************
** Program: wumpus.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Wumpus event class implementation file
** Input: N/A
** Output: N/A
******************************************************/

#include "wumpus.h"

/*********************************************************************
 ** Function: Wumpus()
 ** Description: Default constructor for the wumpus event class
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An wumpus event will be created
 *********************************************************************/
Wumpus::Wumpus() {
	perceptMessage = "You smell a terrible stench.";
	eventID = 'w';
}
