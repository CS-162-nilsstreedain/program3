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
	Event* event;
public:
	Room();
	Event* getEvent() const;
	void setEvent(Event*);
};

#endif /* room_h */
