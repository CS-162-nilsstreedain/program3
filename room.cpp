//
//  room.cpp
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#include "room.h"

Room::Room() {
	this->event = nullptr;
}

Event* Room::getEvent() const {
	return event;
}

void Room::setEvent(Event* event) {
	this->event = event;
}
