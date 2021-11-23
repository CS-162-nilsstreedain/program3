/******************************************************
** Program: room.h
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Room object header file
** Input: N/A
** Output: N/A
******************************************************/

#ifndef room_h
#define room_h

#include <iostream>
#include "event.h"

class Room {
private:
	int Xpos;
	int Ypos;
	Event* event;
public:
	Room(int, int);
	Room(int, int, Event*);
	~Room();
	Event* getEvent() const;
	void setEvent(Event*);

	int getXpos() const;
	int getYpos() const;
};

#endif /* room_h */
