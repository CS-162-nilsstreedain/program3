//
//  room.h
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

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
	Event* getEvent() const;
	void setEvent(Event*);

	int getXpos() const;
	int getYpos() const;
};

#endif /* room_h */
