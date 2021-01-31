#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include "Relation.h"

class Database {
private:
	std::map<std::string, Relation> myMap;

public:
	Database() {}
	void addToDatabase(Relation myRelation) {
		myMap[myRelation.getName()] = myRelation;
	}
	void addTuple(std::string name, Tuple myTuple) {
		myMap[name].addTuple(myTuple);
	}
	std::map<std::string, Relation>* getContents() {
		return &myMap;
	}
};

#endif //DATABASE_H