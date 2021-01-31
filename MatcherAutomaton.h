#ifndef MATCHER_AUTOMATON_H
#define MATCHER_AUTOMATON_H

#include "Automaton.h"
#include <string>

class MatcherAutomaton : public Automaton {
private:
	std::string toMatch = "";
public:
	virtual ~MatcherAutomaton() {}
	MatcherAutomaton(std::string matchString, Token::TokenType tokenType) : Automaton::Automaton(tokenType) { toMatch = matchString; }
	virtual int Read(const std::string& input);
	virtual Token::TokenType getType() {
		return Automaton::type;
	}
	virtual int NewLinesRead() const { return 0; }
};

#endif //MATCHER_AUTOMATON_H