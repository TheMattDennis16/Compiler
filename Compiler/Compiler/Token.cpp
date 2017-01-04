#include "Token.h"

Token::Token(int type, std::string val) : Token()
{
	tokenType = type;
	tokenValue = val;
}

bool Token::operator==(const Token& rhs)
{
	return (tokenType == rhs.tokenType && tokenValue == rhs.tokenValue);
}