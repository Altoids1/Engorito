#include "enigmaMachine.h"
#include "plugboard.h"
#include "rotors.h"




void propagate_rotation() // Whenever a button is pressed, the rightmost rotor is rotated forward *BEFORE GIVING THE ENCODING OF THAT LETTER*
//We do that rotation here.
{

}

std::string Enigma::print_configuration() // Gives a string that describes the current state of this particular Enigma machine.
{
	std::string str = "Rotors: " + std::to_string(r0) + " " + std::to_string(r1) + " " + std::to_string(r2) + "\t"; // The rotors

	str += "Offset: " + std::to_string(offset[0]) + " " + std::to_string(offset[1]) + " " + std::to_string(offset[2]); // The offset of the rotors

	return str;
}


Enigma::Enigma() // Creating an enigma machine with no parameters, so making a random one.
{
	r0 = rand() % 5; // Some random number between 0 and 4
	do {
		r1 = rand() % 5;
	} while (r1 == r0); // prevents the same rotor being used twice
	do {
		r2 = rand() % 5;
	} while (r2 == r0 || r2 == r1); // ditto 

	rotors[0] = Rotors::wheels[r0];
	rotors[1] = Rotors::wheels[r1];
	rotors[2] = Rotors::wheels[r2];

	offset[0] = rand() % 26;
	offset[1] = rand() % 26;
	offset[2] = rand() % 26;
}