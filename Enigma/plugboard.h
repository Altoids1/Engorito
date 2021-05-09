#pragma once
#include "forward.h"



/*	everything about plugboard!
* 
*/	

class plugboard {


private:

	// stores the status of plugboard!
	std::unordered_map<int, int> plugboard_map;



public:

		plugboard();					//constructer
			~plugboard();				//deconstructer


	/*	resolve plugboard
	*	return result of passing a character into the plugboard
	*/
	int resolvePlugboard(int recieve, std::unordered_map<int, int> plugBoard);

	/*	getPlugboard
	*	return status of plugboard
	*/
	std::string getPlugboard(std::unordered_map<int, int> plugboard_map);

	/*	configurePlugboard
	*	changes current plugboard config inplace
	*/
	void changePlugboard(std::unordered_map<int, int> plugboard_map);

	/* randomPlugboard
	*	return a random plugboardconfig
	*/
	std::unordered_map<int, int> randomPlugboard();
};