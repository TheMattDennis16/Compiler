#include "TokenCollection.h"

TokenCollection::TokenCollection()
{
	//Can't store identifiers, they're the final resort of token checking.

	//Basic raw types
	_collection.insert({ std::string("int8"),    Token(TokenTypes::TYPE, "int8") });
	_collection.insert({ std::string("int16"),    Token(TokenTypes::TYPE, "int16") });
	_collection.insert({ std::string("int32"),    Token(TokenTypes::TYPE, "int32") });
	_collection.insert({ std::string("int64"),    Token(TokenTypes::TYPE, "int64") });
	_collection.insert({ std::string("char"),   Token(TokenTypes::TYPE, "char") });
	_collection.insert({ std::string("bool"),   Token(TokenTypes::TYPE, "bool") });
	_collection.insert({ std::string("double"), Token(TokenTypes::TYPE, "double") });
	_collection.insert({ std::string("void"),   Token(TokenTypes::TYPE, "void") });

	//Language constructs
	_collection.insert({ std::string("if"),     Token(TokenTypes::KEYWORD, "if") });
	_collection.insert({ std::string("while"),  Token(TokenTypes::KEYWORD, "while") });
	_collection.insert({ std::string("for"),    Token(TokenTypes::KEYWORD, "for") });
	_collection.insert({ std::string("else"),   Token(TokenTypes::KEYWORD, "else") });
	_collection.insert({ std::string("return"), Token(TokenTypes::KEYWORD, "return") });
	_collection.insert({ std::string("class"),  Token(TokenTypes::KEYWORD, "class") });

	_collection.insert({ std::string("true"),   Token(TokenTypes::VAR_VALUE, "true") });
	_collection.insert({ std::string("false"),  Token(TokenTypes::VAR_VALUE, "false") });
	
	//Basic operators (no modulo)
	_collection.insert({ std::string("++"), Token(TokenTypes::OPERATOR, "++") });//
	_collection.insert({ std::string("--"), Token(TokenTypes::OPERATOR, "--") });//
	_collection.insert({ std::string("="),  Token(TokenTypes::OPERATOR, "=") }); //
	_collection.insert({ std::string("=="), Token(TokenTypes::OPERATOR, "==") });//
	_collection.insert({ std::string("!="), Token(TokenTypes::OPERATOR, "!=") });//
	_collection.insert({ std::string(">"),  Token(TokenTypes::OPERATOR, ">") });//
	_collection.insert({ std::string(">="), Token(TokenTypes::OPERATOR, ">=") });//
	_collection.insert({ std::string("<"),  Token(TokenTypes::OPERATOR, "<") });//
	_collection.insert({ std::string("<="), Token(TokenTypes::OPERATOR, "<=") });//
	_collection.insert({ std::string("/="), Token(TokenTypes::OPERATOR, "/=") });//
	_collection.insert({ std::string("/"),  Token(TokenTypes::OPERATOR, "/") });//
	_collection.insert({ std::string("+="), Token(TokenTypes::OPERATOR, "+=") });//
	_collection.insert({ std::string("+"),  Token(TokenTypes::OPERATOR, "+") });//
	_collection.insert({ std::string("-="), Token(TokenTypes::OPERATOR, "-=") });//
	_collection.insert({ std::string("-"),  Token(TokenTypes::OPERATOR, "-") });//

	_collection.insert({ std::string("*="), Token(TokenTypes::OPERATOR, "*=") });//
	_collection.insert({ std::string("*"),  Token(TokenTypes::OPERATOR, "*") });//
	_collection.insert({ std::string("||"), Token(TokenTypes::OPERATOR, "||") });//
	_collection.insert({ std::string("&&"), Token(TokenTypes::OPERATOR, "&&") });//

	//composite operators seperated by an index
	_collection.insert({ std::string("["), Token(TokenTypes::OPERATOR, "[") });
	_collection.insert({ std::string("]"), Token(TokenTypes::OPERATOR, "]") });

	//general symbols to parse out
	_collection.insert({ std::string("("),  Token(TokenTypes::SYMBOL, "(") });
	_collection.insert({ std::string(")"),  Token(TokenTypes::SYMBOL, ")") });
	_collection.insert({ std::string("{"),  Token(TokenTypes::SYMBOL, "{") });
	_collection.insert({ std::string("}"),  Token(TokenTypes::SYMBOL, "}") });
	_collection.insert({ std::string(";"),  Token(TokenTypes::SYMBOL, ";") });
	_collection.insert({ std::string(","),  Token(TokenTypes::SYMBOL, ",") });
	_collection.insert({ std::string("\""), Token(TokenTypes::SYMBOL, "\"") });
	_collection.insert({ std::string("\'"), Token(TokenTypes::SYMBOL, "\'") });
}

Token TokenCollection::isToken(std::string strToken)
{
	if (_collection.find(strToken) != _collection.end())
		return _collection.at(strToken);
	else return Token();
}

bool TokenCollection::isStringBreakingChar(char tokenChar)
{
	if (isToken(std::string("") + tokenChar).tokenType != TokenTypes::NOT_TOKEN || tokenChar == ' ')
		return true;
	return false;
}