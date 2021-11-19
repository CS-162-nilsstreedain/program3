//
//  rope.hpp
//  Program 3
//
//  Created by Nils Streedain on 11/19/21.
//

#ifndef rope_h
#define rope_h

#include <iostream>
#include "event.h"

class Rope : public Event {
public:
	Rope();
	void encounter() override;
};

#endif /* rope_h */
