//
//  wumpus.h
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#ifndef wumpus_h
#define wumpus_h

#include <iostream>
#include "event.h"

class Wumpus : public Event {
public:
	Wumpus();
	void encounter() override;
};

#endif /* wumpus_h */
