/******************************************************
** Program: bats.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Bats event class implementation file
** Input: N/A
** Output: N/A
******************************************************/

#include "bats.h"

/*********************************************************************
 ** Function: Bats()
 ** Description: Default constructor for the bats event class
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An bats event will be created
 *********************************************************************/
Bats::Bats() {
	perceptMessage = "You hear wings flapping.";
	eventID = 'b';
}
