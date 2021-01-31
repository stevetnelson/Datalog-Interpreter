#include "Interpreter.h"

void Interpreter::interpret() {
	for (unsigned int i = 0; i < (*myProgram->getSchemes()).size(); ++i) {
		std::string name = (*myProgram->getSchemes()).at(i)->getName();
		std::vector<std::string> tempVector;
		for (unsigned int j = 0; j < (*(*myProgram->getSchemes()).at(i)->getContent()).size(); ++j) {
			tempVector.push_back((*(*myProgram->getSchemes()).at(i)->getContent()).at(j)->toString());
		}
		Header header(tempVector);
		Relation myRelation(header, name);
		myDatabase.addToDatabase(myRelation);
	}
	for (unsigned int i = 0; i < (*myProgram->getFacts()).size(); ++i) {
		std::string name = (*myProgram->getFacts()).at(i)->getName();
		Tuple myTuple;
		for (unsigned int j = 0; j < (*(*myProgram->getFacts()).at(i)->getContent()).size(); ++j) {
			myTuple.addElement((*(*myProgram->getFacts()).at(i)->getContent()).at(j)->toString());
		}
		myDatabase.addTuple(name, myTuple);
	}
}
Relation* Interpreter::evaluatePredicate(Predicate* myQuery) {
	std::vector<std::string> stringHolder;
	std::vector<int> intHolder;
	Relation* myRelation = new Relation((*myDatabase.getContents())[myQuery->getName()].getHeader(), myQuery->getName());
	for (Tuple myTuple : (*(*myDatabase.getContents())[myQuery->getName()].getElements())) {
		myRelation->addTuple(myTuple);
	}
	Relation* tempRelationPointer;
	for (unsigned int i = 0; i < (*myQuery->getContent()).size(); ++i) {
		if ((*myQuery->getContent()).at(i)->isConst() == true) {
			tempRelationPointer = myRelation->select(i, (*myQuery->getContent()).at(i)->toString());
			delete myRelation;
			myRelation = tempRelationPointer;
		}
		else {
			bool variableAlreadyExists = false;
			int indexHolder = 0;
			for (unsigned int j = 0; j < stringHolder.size(); ++j) {
				if (stringHolder.at(j) == (*myQuery->getContent()).at(i)->toString()) {
					variableAlreadyExists = true;
					indexHolder = j;
				}
			}
			if (variableAlreadyExists) {
				tempRelationPointer = myRelation->select(indexHolder, i);
				delete myRelation;
				myRelation = tempRelationPointer;
			}
			else {
				stringHolder.push_back((*myQuery->getContent()).at(i)->toString());
				intHolder.push_back(i);
			}
		}
	}
	if (stringHolder.size() > 0) {
		tempRelationPointer = myRelation->project(intHolder);
		delete myRelation;
		myRelation = tempRelationPointer;
		tempRelationPointer = myRelation->rename(stringHolder);
		delete myRelation;
		myRelation = tempRelationPointer;
		myRelation->setVariable(true);
	}
	return myRelation;
}
void Interpreter::evaluateQueries() {
	std::cout << "Query Evaluation" << std::endl;
	for (unsigned int i = 0; i < (*myProgram->getQueries()).size(); ++i) {
		Relation* myRelation = evaluatePredicate((*myProgram->getQueries()).at(i));
		std::cout << (*myProgram->getQueries()).at(i)->toString() << "? ";
		if ((*myRelation->getElements()).size() > 0) {
			std::cout << "Yes(" << (*myRelation->getElements()).size() << ")" << std::endl;
			if (myRelation->getVariable()) {
				myRelation->printRelation();
			}
		}
		else {
			std::cout << "No" << std::endl;
		}
		delete myRelation;
	}
}

void Interpreter::evalueateRules() {
	myGraph->toString();
	myGraph->DFS();
	myGraph->DFSForest();
	std::vector<std::set<int>> SCC = myGraph->getSCC();
	std::cout << "Rule Evaluation" << std::endl;
	for (unsigned int k = 0; k < SCC.size(); ++k) {
		std::set<int>::iterator myIterator = SCC.at(k).begin();
		std::cout << "SCC: R" << *myIterator;
		myIterator++;
		while (myIterator != SCC.at(k).end()) {
			std::cout << ",R" << *myIterator;
			myIterator++;
		}
		std::cout << std::endl;
		if (SCC.at(k).size() == 1 && !(myGraph->ruleDependsOnItself(*(SCC.at(k).begin())))) {
			int c = *(SCC.at(k).begin());
			std::cout << (*myProgram->getRules()).at(c)->toString() << "." << std::endl;
			std::vector<Relation*> evaluatedPredicates;
			for (unsigned int j = 0; j < (*(*myProgram->getRules()).at(c)->getPredicates()).size(); ++j) {
				evaluatedPredicates.push_back(evaluatePredicate((*(*myProgram->getRules()).at(c)->getPredicates()).at(j)));
			}

			Relation* mainRelation = evaluatedPredicates.at(0);
			Relation* tempRelation;
			for (unsigned int i = 0; i < evaluatedPredicates.size() - 1; ++i) {
				tempRelation = naturalJoin(mainRelation, evaluatedPredicates.at(i + 1));
				mainRelation = tempRelation;
			}
			for (unsigned int i = 0; i < evaluatedPredicates.size() - 1; ++i) {
				delete evaluatedPredicates.at(i + 1);
			}

			tempRelation = setAccordingHeadPred((*myProgram->getRules()).at(c)->getHeadPredicate(), mainRelation);
			mainRelation = tempRelation;

			std::string schemeName = (*myProgram->getRules()).at(c)->getHeadPredicate()->getName();
			for (Tuple myTuple : (*mainRelation->getElements())) {
				if ((*(*myDatabase.getContents())[schemeName].getElements()).insert(myTuple).second) {
					std::cout << "  ";
					unsigned int j = 0;
					for (j = 0; j < (*mainRelation->getHeader().getAttributes()).size() - 1; ++j) {
						std::cout << (*(*myDatabase.getContents())[schemeName].getHeader().getAttributes()).at(j) << "=" << myTuple.getValues().at(j) << ", ";
					}
					std::cout << (*(*myDatabase.getContents())[schemeName].getHeader().getAttributes()).at(j) << "=" << myTuple.getValues().at(j) << std::endl;
				}
				myDatabase.addTuple(schemeName, myTuple);
			}
			delete mainRelation;
			std::cout << 1 << " passes: ";
			myIterator = SCC.at(k).begin();
			std::cout << "R" << *(SCC.at(k).begin()) << std::endl;
		}
		else {
			bool ruleTupleAdded = true;
			int numIterations = 0;
			while (ruleTupleAdded) {
				numIterations++;
				ruleTupleAdded = false;
				for (int c : SCC.at(k)) {
					std::cout << (*myProgram->getRules()).at(c)->toString() << "." << std::endl;
					std::vector<Relation*> evaluatedPredicates;
					for (unsigned int j = 0; j < (*(*myProgram->getRules()).at(c)->getPredicates()).size(); ++j) {
						evaluatedPredicates.push_back(evaluatePredicate((*(*myProgram->getRules()).at(c)->getPredicates()).at(j)));
					}

					Relation* mainRelation = evaluatedPredicates.at(0);
					Relation* tempRelation;
					for (unsigned int i = 0; i < evaluatedPredicates.size() - 1; ++i) {
						tempRelation = naturalJoin(mainRelation, evaluatedPredicates.at(i + 1));
						mainRelation = tempRelation;
					}
					for (unsigned int i = 0; i < evaluatedPredicates.size() - 1; ++i) {
						delete evaluatedPredicates.at(i + 1);
					}

					tempRelation = setAccordingHeadPred((*myProgram->getRules()).at(c)->getHeadPredicate(), mainRelation);
					mainRelation = tempRelation;

					std::string schemeName = (*myProgram->getRules()).at(c)->getHeadPredicate()->getName();
					for (Tuple myTuple : (*mainRelation->getElements())) {
						if ((*(*myDatabase.getContents())[schemeName].getElements()).insert(myTuple).second) {
							ruleTupleAdded = true;
							std::cout << "  ";
							unsigned int j = 0;
							for (j = 0; j < (*mainRelation->getHeader().getAttributes()).size() - 1; ++j) {
								std::cout << (*(*myDatabase.getContents())[schemeName].getHeader().getAttributes()).at(j) << "=" << myTuple.getValues().at(j) << ", ";
							}
							std::cout << (*(*myDatabase.getContents())[schemeName].getHeader().getAttributes()).at(j) << "=" << myTuple.getValues().at(j) << std::endl;
						}
						myDatabase.addTuple(schemeName, myTuple);
					}
					delete mainRelation;
				}
			}
			std::cout << numIterations << " passes: ";
			myIterator = SCC.at(k).begin();
			std::cout << "R" << *myIterator;
			myIterator++;
			while (myIterator != SCC.at(k).end()) {
				std::cout << ",R" << *myIterator;
				myIterator++;
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

Header Interpreter::combineHeader(Header header1, Header header2) {
	Header newHeader((*header1.getAttributes()));
	bool headerElementExists = false;
	for (unsigned int i = 0; i < (*header2.getAttributes()).size(); ++i) {
		headerElementExists = false;
		for (unsigned int j = 0; j < (*header1.getAttributes()).size(); ++j) {
			if ((*header1.getAttributes()).at(j) == (*header2.getAttributes()).at(i)) {
				headerElementExists = true;
			}
		}
		if (!headerElementExists) {
			newHeader.addElement((*header2.getAttributes()).at(i));
		}
	}
	return newHeader;
}

bool Interpreter::isJoinable(const Tuple& tuple1, const Tuple& tuple2, std::vector<int>& index1, std::vector<int>& index2) {
	bool isJoinable = false;
	bool hasBeenFalse = false;
	if (index1.size() == 0 && index2.size() == 0) return true;
	for (unsigned int i = 0; i < index1.size(); ++i) {
		if (tuple1.getValues().at(index1.at(i)) == tuple2.getValues().at(index2.at(i))) {
			isJoinable = true;
			if (hasBeenFalse && isJoinable) return false;
		}
		else {
			hasBeenFalse = true;
			if (hasBeenFalse && isJoinable) return false;
		}
	}
	return isJoinable;
}

Tuple Interpreter::combineTuple(Tuple tuple1, const Tuple& tuple2, std::vector<int>& indexes) {
	for (unsigned int i = 0; i < indexes.size(); ++i) {
		tuple1.addElement(tuple2.getValues().at(indexes.at(i)));
	}
	return tuple1;
}

Relation* Interpreter::naturalJoin(Relation* relation1, Relation* relation2) {
	Header myHeader;
	myHeader = combineHeader(relation1->getHeader(), relation2->getHeader());
	Relation* myRelation = new Relation(myHeader, "");
	std::vector<int> index1;
	std::vector<int> index2;
	std::vector<int> replaceIndexes;
	for (unsigned int i = 0; i < (*relation2->getHeader().getAttributes()).size(); ++i) {
		replaceIndexes.push_back(i);
		for (unsigned int j = 0; j < (*relation1->getHeader().getAttributes()).size(); ++j) {
			if ((*relation1->getHeader().getAttributes()).at(j) == (*relation2->getHeader().getAttributes()).at(i)) {
				index1.push_back(j);
				index2.push_back(i);
				replaceIndexes.pop_back();
			}
		}
	}
	for (const Tuple& t1 : (*relation1->getTuples())) {
		for (const Tuple& t2 : (*relation2->getTuples())) {
			if (isJoinable(t1, t2, index1, index2)) {
				Tuple newTuple = combineTuple(t1, t2, replaceIndexes);
				myRelation->addTuple(newTuple);
			}
		}
	}
	delete relation1;
	return myRelation;
}

Relation* Interpreter::setAccordingHeadPred(Predicate* headPredicate, Relation* mainRelation) {
	std::vector<int> indexesToKeep;
	for (unsigned int i = 0; i < (*headPredicate->getContent()).size(); ++i) {
		for (unsigned int j = 0; j < (*mainRelation->getHeader().getAttributes()).size(); ++j) {
			if ((*headPredicate->getContent()).at(i)->toString() == (*mainRelation->getHeader().getAttributes()).at(j)) {
				indexesToKeep.push_back(j);
				break;
			}
		}
	}
	Relation* tempRelation = mainRelation->project(indexesToKeep);
	delete mainRelation;
	return tempRelation;
}