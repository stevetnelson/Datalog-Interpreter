#ifndef ID_AUTOMATON_H
#define ID_AUTOMATON_H

#include "Automaton.h"

class IDAutomaton :	public Automaton {
public:
	virtual ~IDAutomaton() {}
	IDAutomaton() : Automaton::Automaton(Token::ID) {}
	virtual int Read(const std::string& input);
	virtual int NewLinesRead() const { return 0; }
	virtual Token::TokenType getType() {
		return Automaton::type;
	}
};

#endif //ID_AUTOMATON_H