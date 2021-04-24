#include "plugboard.h"
//	steckerbrett!
// "When in use during World War II, there were ten connections." -wikipeida

int plugboard::resolvePlugboard(int in_char, std::unordered_map<char, char> plugboard_map){
	return plugboard_map[in_char];
}


std::string plugboard::getPlugboard(std::unordered_map<char, char> plugboard_map) {
	return "plugboard";
}


void changePlugboard(std::unordered_map<char, char> plugboard_map) {

}
