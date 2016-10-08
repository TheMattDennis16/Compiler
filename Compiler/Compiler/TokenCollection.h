#ifndef TOKEN_COLLECTION_HH
#define TOKEN_COLLECTION_HH

#include <unordered_map>

#include "Token.h"
#include "TokenTypes.h"


class TokenCollection
{
private:
	std::unordered_map<std::string, Token> collection;
public:
	TokenCollection();
	Token isToken(std::string strToken);
	bool isStringBreakingChar(char tokenChar);
};
#endif