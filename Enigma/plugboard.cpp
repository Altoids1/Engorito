#include "plugboard.h"
//#include "Rotors.h"
//	steckerbrett!
// "When in use during World War II, there were ten connections." -wikipeida


plugboard::plugboard() {

}

plugboard::~plugboard() {

}


int plugboard::resolvePlugboard(int in_char, std::unordered_map<int, int> plugboard_map){
	
	if (in_char > 25) {
		printf("Plugboard error: Input value was too large\n");
	}
	if (in_char < 0) {
		printf("Plugboard error: Input value was negative somehow??\n");
	}
	
	return plugboard_map.at(in_char);
	//BUG: if input char is outside [0,25], result is undefined.
}


std::string plugboard::getPlugboard(std::unordered_map<int, int> plugboard_map) {

	std::string return_plugboardString;

	for (auto it = plugboard_map.cbegin(); it != plugboard_map.cend(); it++) {

		return_plugboardString += "{ " + std::to_string((*it).first) + ", " + std::to_string((*it).second) + "}\n";
	}

	return return_plugboardString;
}


void plugboard::changePlugboard(std::unordered_map<int, int> plugboard_map) {

}

std::unordered_map<int, int> plugboard::randomPlugboard() {

	std::unordered_map<int, int> new_RandomPlugboard;
	
	// make a list of "plugs" to build new random plug map from
	int manyPlugs[26] = { 0 };

	srand(time(NULL));

	for (int plug = 0; plug < 6; plug++) {												// 10 connections means choose 20 random nodes

		int random_plug = 0;

		do{																				//0 is key for " this is a node, but not paired yet"
			random_plug = rand() % 26;													// 55 is key for "this isnt a node for a plug"
		}while(manyPlugs[random_plug] == 55);

		manyPlugs[random_plug] = 55;
	}

	//encode each connection into a pair to store into the unordered_map, by labeling each node with the same number in the array.
	int label = 1;																		//indices with the same label are mapped to eachother.
	for (int plug = 0; plug < 26; plug++) {

		if (manyPlugs[plug] == 0) {													
			manyPlugs[plug] = label;
			int random_plug = plug;
			while (manyPlugs[random_plug] != 0) {
				random_plug = rand() % 26;
			}

			manyPlugs[random_plug] = label;
			label++;
		}
	}

	//convert array of randomly placed labels => std::pair and then store them into std::unorderd_map
	for (int plug = 0; plug < 26; plug++) {

		int current_plug = manyPlugs[plug];
		if (current_plug != 55) {														//if a random-connection

			for (int pair = plug; pair < 26; pair++) {									//then look for its pair
				if ((manyPlugs[pair] == current_plug) && (pair != plug)) {
					std::pair<int, int> newPair1 = std::make_pair(plug, pair);
					std::pair<int, int> newPair2 = std::make_pair(pair, plug);
					new_RandomPlugboard.insert(newPair1);
					new_RandomPlugboard.insert(newPair2);

					break;
				}
			}
		}
		else {																			//if not on a random connection, then mapped to the same letter
			std::pair<int, int> newPair = std::make_pair(plug, plug);			
			new_RandomPlugboard.insert(newPair);
		}
	}
	return new_RandomPlugboard;
}