#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
private:
	DatalogProgram* myProgram;
	Database myDatabase;
	Relation* evaluatePredicate(Predicate* myQuery);
	Graph* myGraph;
public:
	Interpreter(DatalogProgram* myProgram) : myProgram(myProgram) {
		myGraph = new Graph(myProgram->getRules());
	}
	void interpret();
	void evaluateQueries();
	void evalueateRules();
	Header combineHeader(Header header1, Header header2);
	bool isJoinable(const Tuple& tuple1, const Tuple& tuple2, std::vector<int>& index1, std::vector<int>& index2);
	Tuple combineTuple(Tuple tuple1, const Tuple& tuple2, std::vector<int>& indexes);
	Relation* naturalJoin(Relation* relation1, Relation* relation2);
	Relation* setAccordingHeadPred(Predicate* headPredicate, Relation* mainRelation);
};

#endif //INTERPRETER_H