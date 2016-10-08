#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>

class Token
{
private:
public:
	int tokenType;
	std::string tokenValue;


	Token(int type, std::string val);
	Token() { tokenType = 100; tokenValue = ""; }
};

#endif