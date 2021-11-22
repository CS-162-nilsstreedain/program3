/******************************************************
** Program: room.cpp
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Room class implementation file
** Input: N/A
** Output: N/A
******************************************************/

#include "room.h"
#include "empty.h"

/*********************************************************************
 ** Function: Room()
 ** Description: Constructor for the room class
 ** Parameters: int Xpos, int Ypos
 ** Pre-Conditions: Xpos & Ypos must be provided
 ** Post-Conditions: An empty room will be created
 *********************************************************************/
Room::Room(int Xpos, int Ypos) {
	this->Xpos = Xpos;
	this->Ypos = Ypos;
	this->event = new Empty;
}

/*********************************************************************
 ** Function: ~Room()
 ** Description: Destructor for the room class
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: A room object will be deleted
 *********************************************************************/
Room::~Room() {
	delete this->event;
}

/*********************************************************************
 ** Function: getEvent()
 ** Description: Returns the event of a given room
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The event of a room will be returned
 *********************************************************************/
Event* Room::getEvent() const {
	return event;
}

/*********************************************************************
 ** Function: setEvent()
 ** Description: Sets the event of a given room
 ** Parameters: Event* event
 ** Pre-Conditions: An event must be provided
 ** Post-Conditions: The event of a room will be set
 *********************************************************************/
void Room::setEvent(Event* event) {
	delete this->event;
	this->event = event;
}

/*********************************************************************
 ** Function: getXpos()
 ** Description: Gets the x-axis position of a given room
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The x-axis position of a room will be returned
 *********************************************************************/
int Room::getXpos() const {
	return Xpos;
}

/*********************************************************************
 ** Function: getYpos()
 ** Description: Gets the y-axis position of a given room
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The y-axis position of a room will be returned
 *********************************************************************/
int Room::getYpos() const {
	return Ypos;
}
