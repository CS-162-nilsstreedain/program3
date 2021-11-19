//
//  main.cpp
//  Program 3
//
//  Created by Nils Streedain on 11/17/21.
//

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include "cave.h"

int verifySizeArgument(char *size) {
	// If size argument is left empty, an exception is thrown.
	if (size == NULL)
		throw std::invalid_argument("No size provided.");
	
	if (!(std::atoi(size) > 3))
		throw std::invalid_argument("Invalid size");
	
	return atoi(size);
}

bool verifyDebugArgument(char *debugMode) {
	// If debug argument is left empty, an exception is thrown.
	if (debugMode == NULL)
		throw std::invalid_argument("No debug mode provided.");
	
	// If debug argument is true, true is returned. If false, false is returned.
	if (!strcmp(debugMode, "true"))
		return true;
	else if (!strcmp(debugMode, "false"))
		return false;
	
	// If debug argument is anything else, an exception is thrown.
	throw std::invalid_argument("Invalid debug mode argument.");
}

int main(int argc, const char * argv[]) {
	int size = verifySizeArgument((char*)argv[1]);
	bool debugMode = verifyDebugArgument((char*)argv[2]);
	
	Cave cave(size);
	
	cave.print(debugMode);
	
    return 0;
}
