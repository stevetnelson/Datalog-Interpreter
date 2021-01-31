#include "CommentAutomaton.h"

int CommentAutomaton::Read(const std::string& input) {
	int inputRead = 0;
	if (input[0] == '#') {
		inputRead++;
		bool stillComment = true;
		int stringLength = input.size();
		if (input[inputRead] == '|') {
			inputRead = 0;
			stillComment = false;
		}
		while (stillComment) {
			if (inputRead == stringLength) {
				stillComment = false;
			}
			else if (input[inputRead] == '\n') {
				stillComment = false;
			}
			else {
				inputRead++;
			}
		}
	}
	return inputRead;
}