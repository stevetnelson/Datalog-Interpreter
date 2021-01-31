#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "Token.h"

class Automaton {
protected:
	int newLines = 0;

	Token::TokenType type;
public:
	virtual ~Automaton() {}
	Automaton(Token::TokenType type) { this->type = type; }
	virtual int Read(const std::string& input) = 0;
	//virtual Token* CreateToken(std::string input, int lineNumber) {
	//	return new Token(type, input, lineNumber);
	//}
	virtual int NewLinesRead() const { return newLines; }
	virtual Token::TokenType getType() = 0;
	
};

#endif //AUTOMATON_H