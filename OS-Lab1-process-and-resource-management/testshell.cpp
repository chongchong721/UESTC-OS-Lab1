#include <iostream>
#include <string>
#include "command_process.h"
int main(int argc,char **argv) {
	command_process("init");
	std::string input;
	FILE* stream1;
	freopen_s(&stream1,argv[1], "r", stdin); //╤анд╪Ч
	while (!std::cin.eof()) {
		std::getline(std::cin, input);
		if (input.empty()) {
			break;
		}
		command_process(input);
	}
	return 0;
}	


