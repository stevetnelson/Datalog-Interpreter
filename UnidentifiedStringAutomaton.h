#ifndef UNIDENTIFIED_STRING_AUTOMATON_H
#define UNIDENTIFIED_STRING_AUTOMATON_H

#include "Automaton.h"

class UnidentifiedStringAutomaton : public Automaton {
private:
	int newLines = 0;
public:
	virtual ~UnidentifiedStringAutomaton() {}
	UnidentifiedStringAutomaton() : Automaton::Automaton(Token::UNDEFINED) {}
	virtual int Read(const std::string& input);
	virtual int NewLinesRead() const { return newLines; }
	virtual Token::TokenType getType() {
		return Automaton::type;
	}
};

#endif //UNIDENTIFIED_STRING_AUTOMATON_H