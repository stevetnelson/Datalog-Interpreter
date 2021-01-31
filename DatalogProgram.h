#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include <string>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
private:
	std::vector<Predicate*> schemes;
	std::vector<Predicate*> facts;
	std::vector<Predicate*> queries;
	std::vector<Rule*> rules;
public:
	~DatalogProgram() {
		for (unsigned int i = 0; i < schemes.size(); ++i) {
			delete schemes.at(i);
		}
		for (unsigned int i = 0; i < facts.size(); ++i) {
			delete facts.at(i);
		}
		for (unsigned int i = 0; i < queries.size(); ++i) {
			delete queries.at(i);
		}
		for (unsigned int i = 0; i < rules.size(); ++i) {
			delete rules.at(i);
		}
	}
	DatalogProgram() {}
	void addScheme(Predicate* scheme) {
		schemes.push_back(scheme);
	}
	void addFact(Predicate* fact) {
		facts.push_back(fact);
	}
	void addRule(Rule* rule) {
		rules.push_back(rule);
	}
	void addQuery(Predicate* query) {
		queries.push_back(query);
	}
	std::vector<Predicate*>* getSchemes() {
		return &schemes;
	}
	std::vector<Predicate*>* getFacts() {
		return &facts;
	}
	std::vector<Predicate*>* getQueries() {
		return &queries;
	}
	std::vector<Rule*>* getRules() {
		return &rules;
	}
};

#endif //DATALOG_PROGRAM_H