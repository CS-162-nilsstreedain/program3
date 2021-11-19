//
//  pit.hpp
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#ifndef pit_h
#define pit_h

#include <iostream>
#include "event.h"

class Pit : public Event {
public:
	Pit();
	void encounter() override;
};

#endif /* pit_h */
