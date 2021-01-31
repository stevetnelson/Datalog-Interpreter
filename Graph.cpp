#include "Graph.h"

Graph::Graph(std::vector<Rule*>* myRules) {
	for (unsigned int i = 0; i < (*myRules).size(); ++i) {
		dependencyGraph[i];
		reverseGraph[i];
	}
	for (unsigned int i = 0; i < (*myRules).size(); ++i) {
		for (unsigned int j = 0; j < (*(*myRules).at(i)->getPredicates()).size(); ++j) {
			for (unsigned int k = 0; k < (*myRules).size(); ++k) {
				if ((*(*myRules).at(i)->getPredicates()).at(j)->getName() == (*myRules).at(k)->getHeadPredicate()->getName()) {
					dependencyGraph[i].insert(k);
					reverseGraph[k].insert(i);
				}
			}
		}
	}
}

void Graph::toString() {
	std::map<int, std::set<int>>::iterator it;
	std::cout << "Dependency Graph\n";
	for (it = dependencyGraph.begin(); it != dependencyGraph.end(); it++) {
		std::cout << "R" << it->first << ":";
		if (it->second.size() > 0) {
			std::set<int>::iterator myIter = it->second.begin();
			std::cout << "R" << *myIter;
			myIter++;
			while (myIter != it->second.end()) {
				std::cout << ",R" << *myIter;
				myIter++;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Graph::DFS() {
	std::vector<bool> verticesSeen;
	for (unsigned int i = 0; i < reverseGraph.size(); ++i) {
		verticesSeen.push_back(false);
	}
	for (unsigned int i = 0; i < reverseGraph.size(); ++i) {
		if (!verticesSeen.at(i)) {
			DFSRecur(i, verticesSeen);
		}
	}
}

void Graph::DFSRecur(int v, std::vector<bool>& verticesSeen) {
	verticesSeen.at(v) = true;
	std::set<int>::iterator iter = reverseGraph[v].begin();
	for (unsigned int i = 0; i < reverseGraph[v].size(); ++i) {
		if (!verticesSeen.at(*iter)) {
			DFSRecur(*iter, verticesSeen);
		}
		++iter;
	}
	postOrderTraversal.push(v);
}

void Graph::DFSForest() {
	std::vector<bool> verticesSeen;
	for (unsigned int i = 0; i < dependencyGraph.size(); ++i) {
		verticesSeen.push_back(false);
	}
	while (postOrderTraversal.size() > 0) {
		if (!verticesSeen.at(postOrderTraversal.top())) {
			std::set<int> mySet;
			DFSForestRecur(postOrderTraversal.top(), verticesSeen, mySet);
			SCC.push_back(mySet);
		}
		postOrderTraversal.pop();
	}
}


std::set<int> Graph::DFSForestRecur(int v, std::vector<bool>& verticesSeen, std::set<int>& mySet) {
	verticesSeen.at(v) = true;
	std::set<int>::iterator iter = dependencyGraph[v].begin();
	for (unsigned int i = 0; i < dependencyGraph[v].size(); ++i) {
		if (!verticesSeen.at(*iter)) {
			DFSForestRecur(*iter, verticesSeen, mySet);
		}
		++iter;
	}
	mySet.insert(v);
	return mySet;
}

bool Graph::ruleDependsOnItself(int ruleToCheck) {
	std::set<int>::iterator iter = dependencyGraph[ruleToCheck].begin();
	for (unsigned int i = 0; i < dependencyGraph[ruleToCheck].size(); ++i) {
		if (*iter == ruleToCheck) {
			return true;
		}
		++iter;
	}
	return false;
}