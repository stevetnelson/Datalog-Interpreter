#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <stack>
#include <iostream>
#include "Rule.h"

class Graph {
private:
	std::map<int, std::set<int>> dependencyGraph;
	std::map<int, std::set<int>> reverseGraph;
	std::vector<std::set<int>> SCC;
	std::stack<int> postOrderTraversal;

public:
	Graph(std::vector<Rule*>* myRules);
	void toString();
	std::vector<std::set<int>> getSCC() {
		return SCC;
	}
	void DFS();
	void DFSRecur(int v, std::vector<bool>& verticesSeen);
	void DFSForest();
	std::set<int> DFSForestRecur(int v, std::vector<bool>& verticesSeen, std::set<int>& mySet);
	bool ruleDependsOnItself(int ruleToCheck);
};

#endif //GRAPH_H