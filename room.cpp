//
//  room.cpp
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#include "room.h"
#include "empty.h"

Room::Room(int Xpos, int Ypos) {
	this->Xpos = Xpos;
	this->Ypos = Ypos;
	this->event = new Empty;
}

Event* Room::getEvent() const {
	return event;
}

void Room::setEvent(Event* event) {
	this->event = event;
}

int Room::getXpos() const {
	return Xpos;
}

int Room::getYpos() const {
	return Ypos;
}
