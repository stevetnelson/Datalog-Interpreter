#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
	enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF_};
private:
	TokenType typeOfToken;
	std::string value;
	int lineNum;
public:
	Token(TokenType type, std::string input, int lineNumber) : typeOfToken(type), value(input), lineNum(lineNumber) {}
	std::string tokenToString(TokenType type);
	std::string toString() {
		std::string outputString = "(";
		outputString += Token::tokenToString(this->typeOfToken);
		outputString += ",\"";
		outputString += this->value;
		outputString += "\",";
		outputString += std::to_string(this->lineNum);
		outputString += ")";
		return outputString;
	}
	std::string getTypeString() {
		return Token::tokenToString(this->typeOfToken);
	}
	std::string getValue() {
		return value;
	}
};

#endif //TOKEN_H