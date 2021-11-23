/******************************************************
** Program: event.h
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Event object header file
** Input: N/A
** Output: N/A
******************************************************/

#ifndef event_h
#define event_h

#include <iostream>

class Event {
protected:
	std::string perceptMessage;
	char eventID;
public:
	Event();
	
	void percept() const;
	char getId() const;
};

#endif /* event_h */
