/*
GOAL:

1. Create a working enigma machine object.
2. Write some cracking algorithms to use against Enigma messages.

*/

//#include "enigmaMachine.h"
#include "plugboard.h"






int main(int argc, char** argv) // Later on we'll be able to take arguments; right now we're just doing debug stuff in here
{
	//Enigma eng;
	plugboard pb;

	//std::cout << eng.print_configuration() << std::endl;

	std::unordered_map<int, int> new_plugBoard = pb.randomPlugboard();

	std::string str = pb.getPlugboard(new_plugBoard);

	std::cout << str << std::endl;

	std::string helloKoala = "hellomynameiskoala";
	std::string encodeded ;


	for (char c : helloKoala) {
		encodeded += char(pb.resolvePlugboard(int(c) - 97, new_plugBoard) + 97);
	}

	

	std::cout << "Before plugboard, : " << helloKoala << std::endl;
	std::cout << "After plugboard, : " << encodeded << std::endl;

	

	return 0;
}