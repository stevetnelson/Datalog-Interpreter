#ifndef TUPLE_H
#define TUPLE_H

#include <string>
#include <vector>

class Tuple {
private:
	std::vector<std::string> values;

public:
	Tuple() {}
	void addElement(std::string element) {
		values.push_back(element);
	}
	std::vector<std::string> getValues() const {
		return values;
	}
	bool operator<(const Tuple& other) const {
		return (values < other.getValues());
	}
};

#endif //TUPLE_H