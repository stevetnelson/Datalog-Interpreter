#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>
#include <iostream>
#include "Token.h"
#include "DatalogProgram.h"

class Parse {
private:
	std::vector<Token*>& myTokens;
	DatalogProgram* myProgram;
	void checkAndPopTerminal(std::string terminalName);
	void datalogProgram();
	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	void headPredicate(Predicate*& myPredicate);
	void predicate(Predicate*& myPredicate);
	void predicateList(Rule*& myRule);
	void parameterList(Predicate*& myPredicate);
	void stringList(Predicate*& myPredicate);
	void idList(Predicate*& myPredicate);
	void parameter(Predicate*& myPredicate);
	std::string parameter();
	std::string expression();
	std::string operatorNT();
public:
	Parse(std::vector<Token*>& tokens, DatalogProgram* program) : myTokens(tokens), myProgram(program) {}
	void parse();
};

#endif //PARSE_H