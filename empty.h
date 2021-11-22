/******************************************************
** Program: empty.h
** Author: Nils Streedain
** Date: 11/21/2021
** Description: Empty event object header file
** Input: N/A
** Output: N/A
******************************************************/

#ifndef empty_h
#define empty_h

#include <iostream>
#include "event.h"

class Empty : public Event {
public:
	Empty();
};

#endif /* empty_h */
