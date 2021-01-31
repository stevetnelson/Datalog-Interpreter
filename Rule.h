#ifndef RULE_H
#define RULE_H

#include "Predicate.h"
#include <string>
#include <vector>

class Rule {
private:
	Predicate* headPredicate;
	std::vector<Predicate*> ruleList;
public:
	~Rule() {
		delete headPredicate;
		for (unsigned int i = 0; i < ruleList.size(); ++i) {
			delete ruleList.at(i);
		}
	}
	Rule() {}
	void setHeadPredicate(Predicate* myPredicate ) {
		headPredicate = myPredicate;
	}
	void addToRuleList(Predicate* predicateToAdd) {
		ruleList.push_back(predicateToAdd);
	}
	std::string toString() {
		std::string outputString = "";
		outputString = headPredicate->toString() + " :- " + ruleList.at(0)->toString();
		if (ruleList.size() == 1) {
			return outputString;
		}
		for (unsigned int i = 1; i < ruleList.size(); ++i) {
			outputString += "," + ruleList.at(i)->toString();
		}
		return outputString;
	}
	std::vector<Predicate*>* getPredicates() {
		return &ruleList;
	}
	Predicate* getHeadPredicate() {
		return headPredicate;
	}
};

#endif //RULE_H