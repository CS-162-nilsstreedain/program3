//
//  bats.h
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#ifndef bats_h
#define bats_h

#include <iostream>
#include "event.h"

class Bats : public Event {
public:
	Bats();
	void encounter() override;
};

#endif /* bats_h */
