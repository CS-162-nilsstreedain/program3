/******************************************************
** Program: event.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Event class implementation file
** Input: N/A
** Output: N/A
******************************************************/

#include "event.h"

/*********************************************************************
 ** Function: Event()
 ** Description: Default constructor for the event class
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: An event will be created
 *********************************************************************/
Event::Event() {}

/*********************************************************************
 ** Function: percept()
 ** Description: Function to print out event percepts to the command line
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The percept of an event will be printed
 *********************************************************************/
void Event::percept() const {
	std::cout << perceptMessage << std::endl;
}

/*********************************************************************
 ** Function: getId()
 ** Description: Function to get the id of an event
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The character id of an event will be returned
 *********************************************************************/
char Event::getId() const {
	return eventID;
}
