#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>

class Token
{
private:
public:
	int tokenType;
	std::string tokenValue;

	/**
	* Constructor for the Token class.
	* @param type Integer for storing the Token Type. These types are identified in the TokenTypes enumerator. 
	* @param val  String representation of the Token.
	*/
	Token(int type, std::string val);

	/**
	* Default constructor for the Token class. Sets the token type to NOT_TOKEN.
	*/
	Token() { tokenType = 100; tokenValue = ""; }

	/**
	* Implements a deep comparison for the Token class by operator overloading.
	*/
	bool operator==(const Token& rhs);
};

#endif