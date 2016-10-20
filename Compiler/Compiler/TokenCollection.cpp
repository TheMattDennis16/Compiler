#include "TokenCollection.h"

TokenCollection::TokenCollection()
{
	//Can't store identifiers, they're the final resort of token checking.

	//Basic raw types
	collection.insert({ std::string("int"), Token(TokenTypes::TYPE, "int") });
	collection.insert({ std::string("char"), Token(TokenTypes::TYPE, "char") });
	collection.insert({ std::string("bool"), Token(TokenTypes::TYPE, "bool") });
	collection.insert({ std::string("double"), Token(TokenTypes::TYPE, "double") });
	collection.insert({ std::string("void"), Token(TokenTypes::TYPE, "void") });

	//Language constructs
	collection.insert({ std::string("if"), Token(TokenTypes::KEYWORD, "if") });
	collection.insert({ std::string("while"), Token(TokenTypes::KEYWORD, "while") });
	collection.insert({ std::string("for"), Token(TokenTypes::KEYWORD, "for") });
	collection.insert({ std::string("else"), Token(TokenTypes::KEYWORD, "else") });
	collection.insert({ std::string("return"), Token(TokenTypes::KEYWORD, "return") });
	collection.insert({ std::string("true"), Token(TokenTypes::VAR_VALUE, "true") });
	collection.insert({ std::string("false"), Token(TokenTypes::VAR_VALUE, "false") });
	
	//Basic operators (no modulo)
	collection.insert({ std::string("++"), Token(TokenTypes::OPERATOR, "++") });//
	collection.insert({ std::string("--"), Token(TokenTypes::OPERATOR, "--") });//
	collection.insert({ std::string("="), Token(TokenTypes::OPERATOR, "=") }); //
	collection.insert({ std::string("=="), Token(TokenTypes::OPERATOR, "==") });//
	collection.insert({ std::string("!="), Token(TokenTypes::OPERATOR, "!=") });//
	collection.insert({ std::string(">"), Token(TokenTypes::OPERATOR, ">") });//
	collection.insert({ std::string(">="), Token(TokenTypes::OPERATOR, ">=") });//
	collection.insert({ std::string("<"), Token(TokenTypes::OPERATOR, "<") });//
	collection.insert({ std::string("<="), Token(TokenTypes::OPERATOR, "<=") });//
	collection.insert({ std::string("/="), Token(TokenTypes::OPERATOR, "/=") });//
	collection.insert({ std::string("/"), Token(TokenTypes::OPERATOR, "/") });//
	collection.insert({ std::string("+="), Token(TokenTypes::OPERATOR, "+=") });//
	collection.insert({ std::string("+"), Token(TokenTypes::OPERATOR, "+") });//
	collection.insert({ std::string("-="), Token(TokenTypes::OPERATOR, "-=") });//
	collection.insert({ std::string("-"), Token(TokenTypes::OPERATOR, "-") });//

	collection.insert({ std::string("*="), Token(TokenTypes::OPERATOR, "*=") });//
	collection.insert({ std::string("*"), Token(TokenTypes::OPERATOR, "*") });//
	collection.insert({ std::string("||"), Token(TokenTypes::OPERATOR, "||") });//
	collection.insert({ std::string("&&"), Token(TokenTypes::OPERATOR, "&&") });//

	//composite operators seperated by an index
	collection.insert({ std::string("["), Token(TokenTypes::OPERATOR, "[") });
	collection.insert({ std::string("]"), Token(TokenTypes::OPERATOR, "]") });

	//general symbols to parse out
	collection.insert({ std::string("("), Token(TokenTypes::SYMBOL, "(") });
	collection.insert({ std::string(")"), Token(TokenTypes::SYMBOL, ")") });
	collection.insert({ std::string("{"), Token(TokenTypes::SYMBOL, "{") });
	collection.insert({ std::string("}"), Token(TokenTypes::SYMBOL, "}") });
	collection.insert({ std::string(";"), Token(TokenTypes::SYMBOL, ";") });
	collection.insert({ std::string(","), Token(TokenTypes::SYMBOL, ",") });
	collection.insert({ std::string("\""), Token(TokenTypes::SYMBOL, "\"") });
	collection.insert({ std::string("\'"), Token(TokenTypes::SYMBOL, "\'") });
}

Token TokenCollection::isToken(std::string strToken)
{
	if (collection.find(strToken) != collection.end())
		return collection.at(strToken);
	else return Token();
}

bool TokenCollection::isStringBreakingChar(char tokenChar)
{
	if (isToken(std::string("") + tokenChar).tokenType != TokenTypes::NOT_TOKEN || tokenChar == ' ')
		return true;
	return false;
}