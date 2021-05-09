/*
GOAL:

1. Create a working enigma machine object.
2. Write some cracking algorithms to use against Enigma messages.

*/

#include <iostream>
#include <string>

#define LOUD_ENIGMA // Uncomment if you want the machine to give a full readout of each encryption step.

namespace Rotors
{
	/*
	For the sake of performance and other things, we're ditching ASCII
	and using the numbers 0 to 25 to mark the letters of the alphabet.

	They're put into this namespace so that the rest of the code can use single-character variable names w/o overriding these.
	*/
	const char a = 0;
	const char b = 1;
	const char c = 2;
	const char d = 3;
	const char e = 4;
	const char f = 5;
	const char g = 6;
	const char h = 7;
	const char i = 8;
	const char j = 9;
	const char k = 10;
	const char l = 11;
	const char m = 12;
	const char n = 13;
	const char o = 14;
	const char p = 15;
	const char q = 16;
	const char r = 17;
	const char s = 18;
	const char t = 19;
	const char u = 20;
	const char v = 21;
	const char w = 22;
	const char x = 23;
	const char y = 24;
	const char z = 25;

	const char forwardrotors[][26] = {
/*
		{a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z}
*/
		{e, k, m, f, l, g, d, q, v, z, n, t, o, w, y, h, x, u, s, p, a, i, b, r, c, j}, // rotor I
		{a, j, d, k, s, i, r, u, x, b, l, h, w, t, m, c, q, g, z, n, p, y, f, v, o, e}, // rotor II
		{b, d, f, h, j, l, c, p, r, t, x, v, z, n, y, e, i, w, g, a, k, m, u, s, q, o}, // rotor III
		{e, s, o, v, p, z, j, a, y, q, u, i, r, h, x, l, n, f, t, g, k, d, c, m, w, b}, // rotor IV
		{v, z, b, r, g, i, t, y, u, p, s, d, n, h, l, x, a, w, m, j, q, o, f, e, c, k}  // rotor V
	};

	/*
	So, get this:
	When the signal goes backwards through the machine, it actually ends up going... backwards.
	Meaning that a naïve implementation for going backwards would have to be, a for-loop using the above forwardrotors thing
	that finds, like, which one has the A as its value and then returns that index, instead of an easy constant-time access.

	Instead of that, I generated a quick lua script to run through that process for us and have pasted its result here, to be held constant for our program.
	*/
	const char backwardrotors[][26] = {
		{u, w, y, g, a, d, f, p, v, z, b, e, c, k, m, t, h, x, s, l, r, i, n, q, o, j}, // rotor I
		{a, j, p, c, z, w, r, l, f, b, d, k, o, t, y, u, q, g, e, n, h, x, m, i, v, s}, // rotor II
		{t, a, g, b, p, c, s, d, q, e, u, f, v, n, z, h, y, i, x, j, w, l, r, k, o, m}, // rotor III
	};

	const char notch[] = { // The letter upon which the rotor forces the one to its left to rotate.
		r, // rotor I
		f, // rotor II
		w, // rotor III
		k, // rotor IV
		a  // rotor V
	};

	//When the rotors bounce back through themselves, they first stop at the (static) reflector.
	//The reflector implemented below is the UKW-B, the model used by Germany during most of WW2.
	//This array remains multidimensional in case we implement alternative reflectors.
	const char reflectors[][26] =
	{
		{y, r, u, h, q, s, l, d, p, x, n, g, o, k, m, i, e, b, f, z, c, w, v, j, a, t}
	};

	char constexpr to_char(size_t x)
	{
		return char(x + 65);
	}
	char constexpr to_char(char x)
	{
		return char(x + 65);
	}
}


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
		if (offset[2] == Rotors::notch[r0]) // If we're at the point that we make the 2nd rotor turn
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
		button = Rotors::forwardrotors[r0][(button + (26 - offset[0])) % 26];
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 3 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = Rotors::forwardrotors[r1][(button + (26 - offset[1])) % 26];
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 2 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = Rotors::forwardrotors[r2][(button + (26 - offset[2])) % 26];
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 1 Encryption: " << Rotors::to_char(button) << std::endl;
#endif

		//Goes through the reflector
		button = Rotors::reflectors[reflector][button];

#ifdef LOUD_ENIGMA
		std::cout << "Reflector Encryption: " << Rotors::to_char(button) << std::endl;
#endif

		//Passes through each rotor, in reverse order
		button = Rotors::backwardrotors[r2][(button + offset[2]) % 26];
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 1 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = Rotors::backwardrotors[r1][(button + offset[1]) % 26];
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 2 Encryption: " << Rotors::to_char(button) << std::endl;
#endif
		button = Rotors::backwardrotors[r0][(button + offset[0]) % 26];
#ifdef LOUD_ENIGMA
		std::cout << "Wheel 3 Encryption: " << Rotors::to_char(button) << std::endl;
#endif

		//TODO: Put it through the plugboards again, over here
		
#ifdef LOUD_ENIGMA
		std::cout << "Output (Lampboard): " << Rotors::to_char(button) << std::endl;
#endif
		return button; // Done!
	}

	//Analogous to the above but takes in an ASCII character instead of a numeral, as a fancier interface
	//Note that this is how you get press to *return* ASCII, as well.
	char pressASCII(char ascii)
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
			if(retchar != char(-1))
				ret.push_back(retchar);
		}

		return ret;
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

		offset[0] = rand() % 26;
		offset[1] = rand() % 26;
		offset[2] = rand() % 26;
	}

	Enigma(int rot1, int rot2, int rot3, size_t o1, size_t o2, size_t o3) // Creating an engima machine with a VERY SPECIFIC configuration. Note that it lacks plugboard configs at the moment.
		:r0(rot1)
		,r1(rot2)
		,r2(rot3)
		,offset{o1,o2,o3}
	{
	}
};


int main(int argc, char** argv) // Later on we'll be able to take arguments; right now we're just doing debug stuff in here
{
	Enigma eng(0,1,2,25,0,0);

	std::cout << eng.pressASCII("AA");

	return 0;
}