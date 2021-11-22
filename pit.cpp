/******************************************************
** Program: pit.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Pit event class implementation file
** Input: N/A
** Output: N/A
******************************************************/

#include "pit.h"

/*********************************************************************
 ** Function: Pit()
 ** Description: Default constructor for the pit event class
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An pit event will be created
 *********************************************************************/
Pit::Pit() {
	perceptMessage = "You feel a breeze.";
	eventID = 'p';
	
}
