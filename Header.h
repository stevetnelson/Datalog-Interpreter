#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>

class Header {
private:
	std::vector<std::string> attributes;

public:
	Header() {}
	Header(std::vector<std::string> attributes) : attributes(attributes) {}
	void addElement(std::string element) {
		attributes.push_back(element);
	}
	std::vector<std::string>* getAttributes() {
		return &attributes;
	}
};

#endif //HEADER_H