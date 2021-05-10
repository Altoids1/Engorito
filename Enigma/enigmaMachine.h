#pragma once
#include "forward.h"
#include "plugboard.h"
#include "rotors.h"



/*
Each one of these is its own Enigma machine,
with its own rotors, plugs, and reflector dish.
*/
class Enigma
{
	const int reflector = 0;
	int r0, r1, r2; // the numbers of the rotors we have
	//R0 is the RIGHTMOST rotor; these variables go right-to-left as that is the direction the circuit goes when first entering.

	size_t offset[3] = { 0,0,0 };

	void propagate_rotation() // Whenever a button is pressed, the rightmost rotor is rotated forward *BEFORE GIVING THE ENCODING OF THAT LETTER*
	//We do that rotation here.
	{
		offset[0] = (offset[0] + 1) % 26;
		if (offset[0] == Rotors::notch[r0]) // If we're at the point that we make the 2nd rotor turn
		{
			offset[1] = (offset[1] + 1) % 26; // Do that
			if (offset[1] == Rotors::notch[r1]) // If we're at the point that we make the THIRD rotor turn
			{
				offset[2] = (offset[2] + 1) % 26; // Do that
			}
		}

		//printf("{%u, %u, %u}\n", offset[0], offset[1], offset[2]);
	}
public:
	std::string print_configuration() // Gives a string that describes the current state of this particular Enigma machine.
	{
		std::string str = "Rotors: " + std::to_string(r0) + " " + std::to_string(r1) + " " + std::to_string(r2) + "\t"; // The rotors

		str += "Offset: " + std::to_string(offset[0]) + " " + std::to_string(offset[1]) + " " + std::to_string(offset[2]); // The offset of the rotors

		return str;
	}

	//The interface function that's supposed to be you pressing a button on it.
	char press(char button)
	{
#ifdef LOUD_ENIGMA
		std::cout << "Keyboard input: " << Rotors::to_char(button) << std::endl;
#endif

		//TODO: Put it through the plugboards here
		propagate_rotation(); // Wheels rotate BEFORE the character goes through the machine
#ifdef LOUD_ENIGMA
		printf("Rotors position: %c%c%c\n", Rotors::to_char(offset[2]), Rotors::to_char(offset[1]), Rotors::to_char(offset[0]));
#endif
		//Passes through each rotor
		button = (button + offset[0]) % 26; // Move button FORWARD when you go in
		button = Rotors::forwardrotors[r0][button];
		button = (button + (26 - offset[0])) % 26; // and move it BACKWARD when you go out
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 3 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = (button + offset[1]) % 26; // Move button FORWARD when you go in
		button = Rotors::forwardrotors[r1][button];
		button = (button + (26 - offset[1])) % 26; // and move it BACKWARD when you go out
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 2 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = (button + offset[2]) % 26; // Move button FORWARD when you go in
		button = Rotors::forwardrotors[r2][button];
		button = (button + (26 - offset[2])) % 26; // and move it BACKWARD when you go out
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 1 Encryption: " << Rotors::to_char(button) << std::endl;
#endif

		//Goes through the reflector
		button = Rotors::reflectors[reflector][button];

#ifdef LOUD_ENIGMA
		std::cout << "Reflector Encryption: " << Rotors::to_char(button) << std::endl;
#endif

		//Passes through each rotor, in reverse order
		button = (button + offset[2]) % 26; // Move button FORWARD when you go in
		button = Rotors::backwardrotors[r2][button]; //
		button = (button + (26 - offset[2])) % 26; // and move it BACKWARD when you go out
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 1 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = (button + offset[1]) % 26; // Move button FORWARD when you go in
		button = Rotors::backwardrotors[r1][button];
		button = (button + (26 - offset[1])) % 26;
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 2 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = (button + offset[0]) % 26;
		button = Rotors::backwardrotors[r0][button];
		button = (button + (26 - offset[0])) % 26;
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 3 Encryption: " << Rotors::to_char(button) << std::endl;
#endif

		//TODO: Put it through the plugboards again, over here

#ifdef LOUD_ENIGMA
		std::cout << "Output (Lampboard): " << Rotors::to_char(button) << std::endl << "--------------------------\n";
#endif
		return button; // Done!
	}

	//Analogous to the above but takes in an ASCII character instead of a numeral, as a fancier interface
	//Note that this is how you get press to *return* ASCII, as well.
	char pressASCII(const char ascii)
	{
		if (ascii > 64 && ascii < 91) // Capital letter
		{
			return (press(ascii - 65) + 65);
		}
		else if (ascii > 96 && ascii < 123) // Lowercase letter
		{
			return (press(ascii - 97) + 97);
		}

		return -1;
	}

	//An even fancier interface that handles input with std::string
	std::string pressASCII(const std::string& str)
	{
		std::string ret = "";

		for (auto it = str.begin(); it != str.end(); ++it)
		{
			char retchar = pressASCII(*it);
			if (retchar != char(-1))
				ret.push_back(retchar);
		}

		return ret;
	}

	// Creating an enigma machine with no parameters, so making a random one.
	Enigma()
	{
		r0 = rand() % 5; // Some random number between 0 and 4
		do {
			r1 = rand() % 5;
		} while (r1 == r0); // prevents the same rotor being used twice
		do {
			r2 = rand() % 5;
		} while (r2 == r0 || r2 == r1); // ditto 

		offset[0] = rand() % 26;
		offset[1] = rand() % 26;
		offset[2] = rand() % 26;
	}

	// Creating an engima machine with a VERY SPECIFIC configuration. Note that it lacks plugboard configs at the moment.
	Enigma(int rot1, int rot2, int rot3, size_t o1, size_t o2, size_t o3)
		:r0(rot1)
		, r1(rot2)
		, r2(rot3)
		, offset{ o1,o2,o3 }
	{
	}
};