#ifndef BLOCK_COMMENT_AUTOMATON_H
#define BLOCK_COMMENT_AUTOMATON_H

#include "Automaton.h"
class BlockCommentAutomaton : public Automaton {
private:
	int newLines = 0;
public:
	virtual ~BlockCommentAutomaton() {}
	BlockCommentAutomaton() : Automaton::Automaton(Token::COMMENT) {}
	virtual int Read(const std::string& input);
	virtual int NewLinesRead() const { return newLines; }
	virtual Token::TokenType getType() {
		return Automaton::type;
	}
};

#endif //BLOCK_COMMENT_AUTOMATONH