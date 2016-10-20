#include "SyntaxAnalyser.h"

SyntaxAnalyser::SyntaxAnalyser()
{

}

void SyntaxAnalyser::parseToTree(std::list<TaggedLexeme>& tokens)
{
	TaggedLexeme current = *tokens.begin();
	TaggedLexeme next = *tokens.begin()++;
	rootNode = RootNode();
	
	while (tokenIt != tokens.end())
	{
		int type = (*tokenIt).taggedWord.tokenType;
		if (type == TokenTypes::TYPE)
		{
		}
		else if (type == TokenTypes::IDENTIFIER) 
		{
		}
		else if (type == TokenTypes::KEYWORD)
		{
		}
	}
}

void parseStatement()
{

}

void parseExpression()
{

}