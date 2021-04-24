#pragma once
#include "forward.h"



/*	everything about plugboard!
* 
*/	

class plugboard {

public:




	/*	resolvePlugboard
	*	return  result of passing a character into the plugboard
	*/
	int resolvePlugboard(int recieve, std::unordered_map<char, char> plugBoard);

	/*	getPlugboard
	*	return status of plugboard
	*/
	std::string getPlugboard(std::unordered_map<char, char> plugboard_map);

	/*	configurePlugboard
	*	return new plugboard config
	*/
	void changePlugboard(std::unordered_map<char, char> plugboard_map);



private:

	// stores the status of plugboard!
	std::unordered_map<char, char> plugboard_map;

	
};