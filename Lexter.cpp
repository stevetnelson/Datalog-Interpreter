#include "Lexter.h"

Lexter::Lexter() {
	Token::TokenType type = Token::COMMA;
	Automaton* machinePointer = new MatcherAutomaton(",", type);
	machines.push_back(machinePointer);
	type = Token::PERIOD;
	machinePointer = new MatcherAutomaton(".", type);
	machines.push_back(machinePointer);
	type = Token::Q_MARK;
	machinePointer = new MatcherAutomaton("?", type);
	machines.push_back(machinePointer);
	type = Token::LEFT_PAREN;
	machinePointer = new MatcherAutomaton("(", type);
	machines.push_back(machinePointer);
	type = Token::RIGHT_PAREN;
	machinePointer = new MatcherAutomaton(")", type);
	machines.push_back(machinePointer);
	type = Token::COLON;
	machinePointer = new MatcherAutomaton(":", type);
	machines.push_back(machinePointer);
	type = Token::COLON_DASH;
	machinePointer = new MatcherAutomaton(":-", type);
	machines.push_back(machinePointer);
	type = Token::MULTIPLY;
	machinePointer = new MatcherAutomaton("*", type);
	machines.push_back(machinePointer);
	type = Token::ADD;
	machinePointer = new MatcherAutomaton("+", type);
	machines.push_back(machinePointer);
	type = Token::SCHEMES;
	machinePointer = new MatcherAutomaton("Schemes", type);
	machines.push_back(machinePointer);
	type = Token::FACTS;
	machinePointer = new MatcherAutomaton("Facts", type);
	machines.push_back(machinePointer);
	type = Token::RULES;
	machinePointer = new MatcherAutomaton("Rules", type);
	machines.push_back(machinePointer);
	type = Token::QUERIES;
	machinePointer = new MatcherAutomaton("Queries", type);
	machines.push_back(machinePointer);
	machinePointer = new IDAutomaton();
	machines.push_back(machinePointer);
	machinePointer = new StringAutomaton();
	machines.push_back(machinePointer);
	machinePointer = new UnidentifiedStringAutomaton();
	machines.push_back(machinePointer);
	machinePointer = new BlockCommentAutomaton();
	machines.push_back(machinePointer);
	machinePointer = new UndefinedBlockCommentAutomaton();
	machines.push_back(machinePointer);
	machinePointer = new CommentAutomaton();
	machines.push_back(machinePointer);
	maxMachine = machines.at(0);
}

void Lexter::Run(std::string input) {
	while (input.size() > 0) {
		if (input[0] == ' ' || input[0] == '\t') {
			input = input.substr(1);
		}
		else if (input[0] == '\n') {
			input = input.substr(1);
			lineNumber++;
		}
		else {
			maxRead = 0;
			int holder;
			Token* newToken;
			int maxNewLines = 0;
			for (unsigned int i = 0; i < machines.size(); ++i) {
				holder = machines.at(i)->Read(input);
				if (holder > maxRead) {
					maxRead = holder;
					maxMachine = machines.at(i);
					maxNewLines = machines.at(i)->NewLinesRead();
				}
			}
			if (maxRead > 0) {
				newToken = new Token(maxMachine->getType(), input.substr(0, maxRead), lineNumber);
				lineNumber += maxNewLines;
				if (!(newToken->getTypeString() == "COMMENT")) {
					tokens.push_back(newToken);
				}
			}
			else {
				maxRead = 1;
				newToken = new Token(Token::UNDEFINED, input.substr(0, maxRead), lineNumber);
				tokens.push_back(newToken);
			}
			input = input.substr(maxRead);
		}
	}
	Token* eofToken = new Token(Token::EOF_, "", lineNumber);
	tokens.push_back(eofToken);
}