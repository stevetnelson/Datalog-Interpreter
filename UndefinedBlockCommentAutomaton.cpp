#include "UndefinedBlockCommentAutomaton.h"

int UndefinedBlockCommentAutomaton::Read(const std::string& input) {
	newLines = 0;
	int inputRead = 0;
	bool stillComment = true;
	if (input[0] == '#') {
		int stringLength = input.size();
		if (1 == stringLength) { //this magic number is used to check for EOF
			inputRead = 0;
		}
		else {
			if (input[1] == '|') {
				inputRead = 2;
				while (stillComment) {
					if (inputRead == stringLength) {
						stillComment = false;
					}
					else if (input[inputRead] == '\n') {
						newLines++;
						inputRead++;
					}
					else if (input[inputRead] == '|') {
						if (inputRead + 1 == stringLength) {
							inputRead++;
							stillComment = false;
						}
						else if (input[inputRead + 1] == '#') {
							inputRead = 0;
							stillComment = false;
						}
						else {
							inputRead++;
						}
					}
					else {
						inputRead++;
					}
				}
			}
		}
	}
	return inputRead;
}