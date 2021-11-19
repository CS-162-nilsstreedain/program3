//
//  gold.h
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#ifndef gold_h
#define gold_h

#include <iostream>
#include "event.h"

class Gold : public Event {
public:
	Gold();
	void encounter() override;
};

#endif /* gold_h */
