#include <iostream>
#include <string>
#include "command_process.h"
int main() {
	std::string input;
	while (1) {
		std::getline(std::cin, input);
		command_process(input);
	}
}	


