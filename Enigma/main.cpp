/*
GOAL:

1. Create a working enigma machine object.
2. Write some cracking algorithms to use against Enigma messages.

*/

#include <iostream>
#include <string>

namespace Rotors
{
	/*
	For the sake of performance and other things, we're ditching ASCII
	and using the numbers 0 to 25 to mark the letters of the alphabet.

	They're put into this namespace so that the rest of the code can use single-character variable names w/o overriding these.
	*/
	const char a = 1;
	const char b = 2;
	const char c = 3;
	const char d = 4;
	const char e = 5;
	const char f = 6;
	const char g = 7;
	const char h = 8;
	const char i = 9;
	const char j = 10;
	const char k = 11;
	const char l = 12;
	const char m = 13;
	const char n = 14;
	const char o = 15;
	const char p = 16;
	const char q = 17;
	const char r = 18;
	const char s = 19;
	const char t = 20;
	const char u = 21;
	const char v = 22;
	const char w = 23;
	const char x = 24;
	const char y = 25;
	const char z = 26;

	char wheels[][26] = {
		{e, k, m, f, l, g, d, q, v, z, n, t, o, w, y, h, x, u, s, p, a, i, b, r, c, j}, // rotor I
		{a, j, d, k, s, i, r, u, x, b, l, h, w, t, m, c, q, g, z, n, p, y, f, v, o, e}, // rotor II
		{b, d, f, h, j, l, c, p, r, t, x, v, z, n, y, e, i, w, g, a, k, m, u, s, q, o}, // rotor III
		{e, s, o, v, p, z, j, a, y, q, u, i, r, h, x, l, n, f, t, g, k, d, c, m, w, b}, // rotor IV
		{v, z, b, r, g, i, t, y, u, p, s, d, n, h, l, x, a, w, m, j, q, o, f, e, c, k}  // rotor V
	};

	char notch[] = { // The letter upon which the rotor forces the one to its left to rotate.
		q, // rotor I
		e, // rotor II
		v, // rotor III
		j, // rotor IV
		z  // rotor V
	};
}


/*
Each one of these is its own Enigma machine,
with its own rotors, plugs, and reflector dish.
*/
class Enigma 
{
	char* rotors[3];
	int r0, r1, r2; // the numbers of the rotors we have

	size_t offset[3] = { 0,0,0 };

	void propagate_rotation() // Whenever a button is pressed, the rightmost rotor is rotated forward *BEFORE GIVING THE ENCODING OF THAT LETTER*
	//We do that rotation here.
	{

	}
public:
	std::string print_configuration() // Gives a string that describes the current state of this particular Enigma machine.
	{
		std::string str = "Rotors: " + std::to_string(r0) + " " + std::to_string(r1) + " " + std::to_string(r2) + "\t"; // The rotors

		str += "Offset: " + std::to_string(offset[0]) + " " + std::to_string(offset[1]) + " " + std::to_string(offset[2]); // The offset of the rotors

		return str;
	}
	

	Enigma() // Creating an enigma machine with no parameters, so making a random one.
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
};


int main(int argc, char** argv) // Later on we'll be able to take arguments; right now we're just doing debug stuff in here
{
	Enigma eng;

	std::cout << eng.print_configuration();

	return 0;
}