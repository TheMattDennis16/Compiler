#ifndef TOKEN_COLLECTION_HH
#define TOKEN_COLLECTION_HH

#include <unordered_map>

#include "Token.h"
#include "TokenTypes.h"


class TokenCollection
{
private:
	std::unordered_map<std::string, Token> _collection;
public:
	/**
	* Constructor for the TokenCollection class.
	*/
	TokenCollection();

	/**
	* Checks whether the specified string parameter is a valid Token type. Returns the Token if possible.
	* @param strToken The string version to check against the known Token types.
	* @return A new Token instance for a valid match, if the parameter is an invalid Token the return value is defined as an Error type.
	*/
	Token isToken(std::string strToken);

	/**
	* Checks whether or not the character specified is a valid character to break strings.
	* @param tokenChar The character to be checked
	* @return True if the character specified is a character intended to break a stream of characters.
	*/
	bool isStringBreakingChar(char tokenChar);
};
#endif