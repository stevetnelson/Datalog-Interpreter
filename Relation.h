#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <string>
#include <iostream>
#include "Header.h"
#include "Tuple.h"


class Relation {
private:
	std::set<Tuple> myTuples;
	Header myHeader;
	std::string name;
	bool containsVariable = false;
public:
	Relation() {}
	Relation(Header myHeader, std::string name) : myHeader(myHeader), name(name) {}
	std::string getName() {
		return name;
	}
	Header getHeader() {
		return myHeader;
	}
	std::set<Tuple>* getElements() {
		return& myTuples;
	}
	void addTuple(Tuple myTuple) {
		myTuples.insert(myTuple);
	}
	void printRelation() {
		for (Tuple t : myTuples) {
			unsigned int i = 0;
			std::cout << "  ";
			for (i = 0; i < t.getValues().size() - 1; ++i) {
				std::cout << (*myHeader.getAttributes()).at(i) << "=" << t.getValues().at(i) << ", ";
			}
			std::cout << (*myHeader.getAttributes()).at(i) << "=" << t.getValues().at(i) << "" << std::endl;
		}
	}
	void setVariable(bool myBool) {
		containsVariable = myBool;
	}
	bool getVariable() {
		return containsVariable;
	}
	std::set<Tuple>* getTuples() {
		return &myTuples;
	}
	Relation* select(int index, std::string value);
	Relation* select(int index1, int index2);
	Relation* project(std::vector<int> attributesToKeep);
	Relation* rename(std::vector<std::string> newHeader);
	
};

#endif //RELATION_H