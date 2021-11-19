//
//  event.h
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

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
	virtual void encounter()=0;
};

#endif /* event_h */
