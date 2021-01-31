#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter {
private:
	std::string value;
	bool isConstant = false;
public:
	Parameter(std::string parameterValue) : value(parameterValue) {}
	std::string toString() {
		return value;
	}
	void setConstant(bool paramIsConstant) {
		isConstant = paramIsConstant;
	}
	bool isConst() {
		return isConstant;
	}
};

#endif //PARAMETER_H