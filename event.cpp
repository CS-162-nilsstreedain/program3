//
//  event.cpp
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#include "event.h"

Event::Event() {}

void Event::percept() const {
	std::cout << perceptMessage << std::endl;
}

char Event::getId() const {
	return eventID;
}
