#include "StringAutomaton.h"

int StringAutomaton::Read(const std::string& input) {
	newLines = 0;
	int inputRead = 0;
	bool stillString = true;
	if (input[0] == '\'') {
		inputRead = 1;
		int stringLength = input.size();
		while (stillString) {
			if (inputRead == stringLength) {
				inputRead = 0;
				stillString = false;
			}
			else if (input[inputRead] == '\n') {
				newLines++;
				inputRead++;
			}
			else if (input[inputRead] == '\'') {
				if (inputRead + 1 == stringLength) {
					inputRead++;
					stillString = false;
				}
				else if (input[inputRead + 1] == '\'') {
					inputRead = inputRead + 2;
				}
				else {
					inputRead++;
					stillString = false;
				}
			}
			else {
				inputRead++;
			}
		}
	}
	return inputRead;
}