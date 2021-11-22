/******************************************************
** Program: pit.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Pit event class implementation file
** Input: N/A
** Output: N/A
******************************************************/

#include "gold.h"

/*********************************************************************
 ** Function: Gold()
 ** Description: Default constructor for the gold event class
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An gols event will be created
 *********************************************************************/
Gold::Gold() {
	perceptMessage = "You see a glimmer nearby.";
	eventID = 'g';
	
}
