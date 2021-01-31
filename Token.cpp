#include "Token.h"

std::string Token::tokenToString(TokenType type) {
	std::string output;
	switch (type) {
	case COMMA: output = "COMMA";
		break;
	case PERIOD: output = "PERIOD";
		break;
	case Q_MARK: output = "Q_MARK";
		break;
	case LEFT_PAREN: output = "LEFT_PAREN";
		break;
	case RIGHT_PAREN: output = "RIGHT_PAREN";
		break;
	case COLON: output = "COLON";
		break;
	case COLON_DASH: output = "COLON_DASH";
		break;
	case MULTIPLY: output = "MULTIPLY";
		break;
	case ADD: output = "ADD";
		break;
	case SCHEMES: output = "SCHEMES";
		break;
	case FACTS: output = "FACTS";
		break;
	case RULES: output = "RULES";
		break;
	case QUERIES: output = "QUERIES";
		break;
	case ID: output = "ID";
		break;
	case STRING: output = "STRING";
		break;
	case COMMENT: output = "COMMENT";
		break;
	case UNDEFINED: output = "UNDEFINED";
		break;
	case EOF_: output = "EOF";
		break;
	default: break;
	}
	return output;
}