#ifndef STRING_AUTOMATON_H
#define STRING_AUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {
private:
	int newLines = 0;
public:
	virtual ~StringAutomaton() {}
	StringAutomaton() : Automaton::Automaton(Token::STRING) {}
	virtual int Read(const std::string& input);
	virtual int NewLinesRead() const { return newLines; }
	virtual Token::TokenType getType() {
		return Automaton::type;
	}
};

#endif //UNIDENTIFIED_STRING_AUTOMATON_H
