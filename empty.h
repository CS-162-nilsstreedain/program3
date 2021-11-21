//
//  empty.h
//  Program 3
//
//  Created by Nils Streedain on 11/20/21.
//

#ifndef empty_h
#define empty_h

#include <iostream>
#include "event.h"

class Empty : public Event {
public:
	Empty();
	void encounter() override;
};

#endif /* empty_h */
