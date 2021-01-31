#include "Parse.h"

void Parse::checkAndPopTerminal(std::string terminalName) {
	if (myTokens.front()->getTypeString() == terminalName) {
		myTokens.erase(myTokens.begin());
	}
	else {
		throw myTokens.front();
	}
}

void Parse::datalogProgram() {
	checkAndPopTerminal("SCHEMES");
	checkAndPopTerminal("COLON");
	scheme();
	schemeList();
	checkAndPopTerminal("FACTS");
	checkAndPopTerminal("COLON");
	factList();
	checkAndPopTerminal("RULES");
	checkAndPopTerminal("COLON");
	ruleList();
	checkAndPopTerminal("QUERIES");
	checkAndPopTerminal("COLON");
	query();
	queryList();
	checkAndPopTerminal("EOF");
}

void Parse::schemeList() {
	if (myTokens.front()->getTypeString() == "ID") {
		scheme();
		schemeList();
	}
}

void Parse::factList() {
	if (myTokens.front()->getTypeString() == "ID") {
		fact();
		factList();
	}
}

void Parse::ruleList() {
	if (myTokens.front()->getTypeString() == "ID") {
		rule();
		ruleList();
	}
}

void Parse::queryList() {
	if (myTokens.front()->getTypeString() == "ID") {
		query();
		queryList();
	}
}

void Parse::scheme() {
	Predicate* schemePredicate = new Predicate;;
	Parameter* schemeParameter;
	if (myTokens.front()->getTypeString() == "ID") {
		schemePredicate->setName(myTokens.front()->getValue());
	}
	checkAndPopTerminal("ID");
	checkAndPopTerminal("LEFT_PAREN");
	if (myTokens.front()->getTypeString() == "ID") {
		schemeParameter = new Parameter(myTokens.front()->getValue());
		schemePredicate->addToContents(schemeParameter);
	}
	checkAndPopTerminal("ID");
	idList(schemePredicate);
	checkAndPopTerminal("RIGHT_PAREN");
	myProgram->addScheme(schemePredicate);
}

void Parse::fact() {
	Predicate* factPredicate = new Predicate;
	Parameter* factParameter;
	if (myTokens.front()->getTypeString() == "ID") {
		factPredicate->setName(myTokens.front()->getValue());
	}
	checkAndPopTerminal("ID");
	checkAndPopTerminal("LEFT_PAREN");
	if (myTokens.front()->getTypeString() == "STRING") {
		factParameter = new Parameter(myTokens.front()->getValue());
		factPredicate->addToContents(factParameter);
	}
	checkAndPopTerminal("STRING");
	stringList(factPredicate);
	checkAndPopTerminal("RIGHT_PAREN");
	checkAndPopTerminal("PERIOD");
	myProgram->addFact(factPredicate);
}

void Parse::rule() {
	Rule* newRule = new Rule;
	Predicate* myPredicate;
	headPredicate(myPredicate);
	newRule->setHeadPredicate(myPredicate);
	checkAndPopTerminal("COLON_DASH");
	predicate(myPredicate);
	newRule->addToRuleList(myPredicate);
	predicateList(newRule);
	checkAndPopTerminal("PERIOD");
	myProgram->addRule(newRule);
}

void Parse::query() {
	Predicate* queryPredicate;
	predicate(queryPredicate);
	checkAndPopTerminal("Q_MARK");
	myProgram->addQuery(queryPredicate);
}

void Parse::headPredicate(Predicate*& myPredicate) {
	Parameter* myParameter;
	if (myTokens.front()->getTypeString() == "ID") {
		myPredicate = new Predicate(myTokens.front()->getValue());
	}
	checkAndPopTerminal("ID");
	checkAndPopTerminal("LEFT_PAREN");
	if (myTokens.front()->getTypeString() == "ID") {
		myParameter = new Parameter(myTokens.front()->getValue());
		myPredicate->addToContents(myParameter);
	}
	checkAndPopTerminal("ID");
	idList(myPredicate);
	checkAndPopTerminal("RIGHT_PAREN");
}

void Parse::predicate(Predicate*& myPredicate) {
	if (myTokens.front()->getTypeString() == "ID") {
		myPredicate = new Predicate(myTokens.front()->getValue());
	}
	checkAndPopTerminal("ID");
	checkAndPopTerminal("LEFT_PAREN");
	parameter(myPredicate);
	parameterList(myPredicate);
	checkAndPopTerminal("RIGHT_PAREN");
}

void Parse::predicateList(Rule*& myRule) {
	if (myTokens.front()->getTypeString() == "COMMA") {
		checkAndPopTerminal("COMMA");
		Predicate* myPredicate;
		predicate(myPredicate);
		myRule->addToRuleList(myPredicate);
		predicateList(myRule);
	}
}

void Parse::parameterList(Predicate*& myPredicate) {
	if (myTokens.front()->getTypeString() == "COMMA") {
		checkAndPopTerminal("COMMA");
		parameter(myPredicate);
		parameterList(myPredicate);
	}
}

void Parse::stringList(Predicate*& myPredicate) {
	if (myTokens.front()->getTypeString() == "COMMA") {
		checkAndPopTerminal("COMMA");
		if (myTokens.front()->getTypeString() == "STRING") {
			Parameter* myParameter = new Parameter(myTokens.front()->getValue());
			myPredicate->addToContents(myParameter);
		}
		checkAndPopTerminal("STRING");
		stringList(myPredicate);
	}
}

void Parse::idList(Predicate*& myPredicate) {
	if (myTokens.front()->getTypeString() == "COMMA") {
		checkAndPopTerminal("COMMA");
		if (myTokens.front()->getTypeString() == "ID") {
			Parameter* myParameter = new Parameter(myTokens.front()->getValue());
			myPredicate->addToContents(myParameter);
		}
		checkAndPopTerminal("ID");
		idList(myPredicate);
	}
}

void Parse::parameter(Predicate*& myPredicate) {
	if (myTokens.front()->getTypeString() == "STRING") {
		Parameter* myParameter = new Parameter(myTokens.front()->getValue());
		myParameter->setConstant(true);
		myPredicate->addToContents(myParameter);
		myTokens.erase(myTokens.begin());
	}
	else if (myTokens.front()->getTypeString() == "ID") {
		Parameter* myParameter = new Parameter(myTokens.front()->getValue());
		myPredicate->addToContents(myParameter);
		myTokens.erase(myTokens.begin());
	}
	else {
		std::string myString = expression();
		Parameter* myParameter = new Parameter(myString);
		myPredicate->addToContents(myParameter);
	}
}

std::string Parse::parameter() {
	std::string returnString = "";
	if (myTokens.front()->getTypeString() == "STRING") {
		returnString = myTokens.front()->getValue();
		myTokens.erase(myTokens.begin());
	}
	else if (myTokens.front()->getTypeString() == "ID") {
		returnString = myTokens.front()->getValue();
		myTokens.erase(myTokens.begin());
	}
	else {
		returnString = expression();
	}
	return returnString;
}

std::string Parse::expression() {
	std::string expressionString = "";
	if (myTokens.front()->getTypeString() == "LEFT_PAREN") {
		expressionString += "(";
	}
	checkAndPopTerminal("LEFT_PAREN");
	expressionString += parameter();
	expressionString += operatorNT();
	expressionString += parameter();
	if (myTokens.front()->getTypeString() == "RIGHT_PAREN") {
		expressionString += ")";
	}
	checkAndPopTerminal("RIGHT_PAREN");
	return expressionString;
}

std::string Parse::operatorNT() {
	std::string returnString = "";
	if (myTokens.front()->getTypeString() == "ADD") {
		returnString = myTokens.front()->getValue();
		myTokens.erase(myTokens.begin());
		return returnString;
	}
	else if (myTokens.front()->getTypeString() == "MULTIPLY") {
		returnString = myTokens.front()->getValue();
		myTokens.erase(myTokens.begin());
		return returnString;
	}
	else {
		throw myTokens.front();
	}
	return "";
}

void Parse::parse() {
	datalogProgram();
}