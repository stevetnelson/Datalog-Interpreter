#ifndef Lexter_H
#define Lexter_H

#include "Token.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "UnidentifiedStringAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "UndefinedBlockCommentAutomaton.h"
#include "CommentAutomaton.h"
#include <vector>
#include <iostream>

class Lexter {
private:
	std::vector<Token*> tokens;
	std::vector<Automaton*> machines;
	int lineNumber = 1;
	int maxRead = 0;
	Automaton* maxMachine;

public:
	Lexter();
	~Lexter() {
		for (unsigned int i = 0; i < tokens.size(); ++i) {
			delete tokens.at(i);
		}
		for (unsigned int i = 0; i < machines.size(); ++i) {
			delete machines.at(i);
		}
	}
	void Run(std::string input);
	void Print() {
		for (unsigned int i = 0; i < tokens.size(); ++i) {
			std::cout << tokens.at(i)->toString() << std::endl;
		}
		std::cout << "Total Tokens = " << tokens.size() << std::endl;
	}
	std::vector<Token*> GetVector() {
		return tokens;
	}
};

#endif //Lexter_H