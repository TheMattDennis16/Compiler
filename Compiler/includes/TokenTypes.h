#ifndef TOKEN_TYPES_HH
#define TOKEN_TYPES_HH

namespace TokenTypes
{
	enum Types
	{
		IDENTIFIER,
		OPERATOR,
		KEYWORD,
		TYPE,
		WHITESPACE,
		SYMBOL,
		UNEXPECTED,
		VAR_VALUE,
		NOT_TOKEN = 100
	};
}

#endif