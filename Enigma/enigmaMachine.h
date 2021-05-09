#pragma once
#include "forward.h"



/*
Each one of these is its own Enigma machine,
with its own rotors, plugs, and reflector dish.
*/


class Enigma
{
	char* rotors[3];
	int r0, r1, r2;		// the numbers of the rotors we have

	size_t offset[3];

	void propagate_rotation(); // Whenever a button is pressed, the rightmost rotor is rotated forward *BEFORE GIVING THE ENCODING OF THAT LETTER*
	//We do that rotation here.
public:
	std::string print_configuration(); // Gives a string that describes the current state of this particular Enigma machine.
	


	Enigma(); // Creating an enigma machine with no parameters, so making a random one.
};