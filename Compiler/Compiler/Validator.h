#ifndef VALIDATOR_HH
#define VALIDATOR_HH

#include "LexicalAnalyser.h"
#include "RootNode.h"
#include "TokenTypes.h"
#include "FileHandling.h"
#include "TypeParsing.h"

#include "Expr.h"
#include "Function.h"
#include "Assignment.h"
#include "While.h"
#include "For.h"
#include "If.h"
#include "Class.h"
#include "Break.h"
#include "Continue.h"

typedef std::list<TaggedLexeme> taglist;
typedef std::list<TaggedLexeme>::iterator tagIt;

class Validator
{
private:
	int _nestingLevel;
	taglist _tokens;
	tagIt _it; 
	RootNode _rootNode;
	Class* _activeClass;
	Block* _activeBlock;
	Function* _activeFunction;

	TaggedLexeme _getNext();
	If* _validateIf();
	bool _isInLoop();

public:
	Validator(taglist tags);
	std::list<FunctionParameter> validateFunctionParameters();
	bool validateType();
	bool validateClass();
	Node* validateExpression(std::string endSymbol);
	bool validateSyntax();
	bool validateSymbol();
	bool validateStatement();

	// Update to use advanceToToken to move parse past minor non-blocking errors. e.g.
	// Type mismatch, unrecognised identifier, invalid keyword usage, unexpected symbol etc.
	//void advanceToToken(Token& token);
};

#endif