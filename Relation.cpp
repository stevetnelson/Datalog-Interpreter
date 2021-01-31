#include "Relation.h"

Relation* Relation::select(int index, std::string value) {
	Relation* relationToReturn = new Relation(myHeader, name);
	for (Tuple myTuple : myTuples) {
		if (myTuple.getValues().at(index) == value) {
			relationToReturn->addTuple(myTuple);
		}
	}
	return relationToReturn;
}
Relation* Relation::select(int index1, int index2) {
	Relation* relationToReturn = new Relation(myHeader, name);
	for (Tuple myTuple : myTuples) {
		if (myTuple.getValues().at(index1) == myTuple.getValues().at(index2)) {
			relationToReturn->addTuple(myTuple);
		}
	}
	return relationToReturn;
}
Relation* Relation::project(std::vector<int> attributesToKeep) {
	std::vector<std::string> newHeader;
	for (unsigned int i = 0; i < attributesToKeep.size(); ++i) {
		newHeader.push_back((*myHeader.getAttributes()).at(attributesToKeep.at(i)));
	}
	Header myHeader(newHeader);
	Relation* relationToReturn = new Relation(myHeader, name);
	for (Tuple myTuple : myTuples) {
		Tuple inputTuple;
		for (unsigned int i = 0; i < attributesToKeep.size(); ++i) {
			inputTuple.addElement(myTuple.getValues().at(attributesToKeep.at(i)));
		}
		relationToReturn->addTuple(inputTuple);
	}
	return relationToReturn;
}
Relation* Relation::rename(std::vector<std::string> newHeader) {
	Header myHeader(newHeader);
	Relation* relationToReturn = new Relation(myHeader, name);
	for (Tuple myTuple : myTuples) {
		relationToReturn->addTuple(myTuple);
	}
	return relationToReturn;
}
