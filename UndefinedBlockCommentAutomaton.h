#ifndef UNDEFINED_BLOCK_COMMENT_AUTOMATON_H
#define UNDEFINED_BLOCK_COMMENT_AUTOMATON_H

#include "Automaton.h"
class UndefinedBlockCommentAutomaton : public Automaton {
private:
	int newLines = 0;
public:
	virtual ~UndefinedBlockCommentAutomaton() {}
	UndefinedBlockCommentAutomaton() : Automaton::Automaton(Token::UNDEFINED) {}
	virtual int Read(const std::string& input);
	virtual int NewLinesRead() const { return newLines; }
	virtual Token::TokenType getType() {
		return Automaton::type;
	}
};

#endif //UNDEFINED_BLOCK_COMMENT_AUTOMATON_H
