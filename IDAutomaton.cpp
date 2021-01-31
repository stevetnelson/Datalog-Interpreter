#include "IDAutomaton.h"
#include <cctype>

int IDAutomaton::Read(const std::string& input) {
	int inputRead = 0;
	if (isalpha(input[0])) {
		inputRead = 1;
		while (isalpha(input[inputRead]) || isdigit(input[inputRead])) {
			inputRead++;
		}
	}
	return inputRead;
}