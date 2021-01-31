#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>

#include "Parameter.h"

class Predicate {
private:
	std::string predicateName;
	std::vector<Parameter*> predicateContents;
public:
	~Predicate() {
		for (unsigned int i = 0; i < predicateContents.size(); ++i) {
			delete predicateContents.at(i);
		}
	}
	Predicate() {}
	Predicate(std::string name) : predicateName(name) {}
	void addToContents(Parameter* newContent) {
		predicateContents.push_back(newContent);
	}
	std::string toString() {
		std::string outputString = "";
		outputString = predicateName + "(" + predicateContents.at(0)->toString();
		for (unsigned int i = 1; i < predicateContents.size(); ++i) {
			outputString += "," + predicateContents.at(i)->toString();
		}
		outputString += ")";
		return outputString;
	}
	void setName(std::string name) {
		predicateName = name;
	}
	std::string getName() {
		return predicateName;
	}
	std::vector<Parameter*>* getContent() {
		return &predicateContents;
	}
};

#endif //PREDICATE_H