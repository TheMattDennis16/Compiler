#ifndef SYNTAX_ANALYSER_HH
#define SYNTAX_ANALYSER_HH

#include <list>

#include "LexicalAnalyser.h"
#include "RootNode.h"
#include "Node.h"

class SyntaxAnalyser
{
private:
	std::list<TaggedLexeme>::iterator tokenIt;
	RootNode rootNode;
public:
	SyntaxAnalyser();
	void advanceToToken(Token& token);
	void parseToTree(std::list<TaggedLexeme>& tokens);
	void getNodeType(TaggedLexeme& lex);
	void parseStatement();
	void parseExpression();
};

#endif