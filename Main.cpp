#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "Lexter.h"
#include "Parse.h"
#include "DatalogProgram.h"
#include "Interpreter.h"
using namespace std;

int main(int argc, char* argv[]) {
	//open input/output files and check for errors that may have occured while opening
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
	}
	
	//copy the entire file into a string
	std::ostringstream sstring;
	sstring << in.rdbuf();
	string fileContents = sstring.str();
	in.close();
	
	//parse then run program
	DatalogProgram myProgram;
	vector<Token*> tokenVector;
	Lexter myLexter;
	myLexter.Run(fileContents);
	tokenVector = myLexter.GetVector();
	Parse myParse(tokenVector, &myProgram);
	try {
		myParse.parse();
	}
	catch (Token* token) {
		cout << "Failure!" << endl << "  " << token->toString() << endl;
	}
	Interpreter myInterpreter(&myProgram);
	myInterpreter.interpret();
	myInterpreter.evalueateRules();
	myInterpreter.evaluateQueries();

	//deallocation will take place when deconstructors are called
	return 0;
}