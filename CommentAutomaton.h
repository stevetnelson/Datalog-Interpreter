#ifndef COMMENT_AUTOMATON_H
#define COMMENT_AUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {
public:
	virtual ~CommentAutomaton() {}
	CommentAutomaton() : Automaton::Automaton(Token::COMMENT) {}
	virtual int Read(const std::string& input);
	virtual int NewLinesRead() const { return 0; }
	virtual Token::TokenType getType() {
		return Automaton::type;
	}
};

#endif //COMMENT_AUTOMATON_H