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

	/*
	* Increments the iterator to load the next available TaggedLexeme. This updates the private _it Iterator for the tag std::list
	*/
	TaggedLexeme _getNext();

	/**
	* Validate that the IF statement follows expected syntax, and that it contains an Expression.
	* Defer validation of type to next phase.
	* @return A pointer to an If node containing the Expression and a pointer to its new associated block.
	*/
	If* _validateIf();

	/**
	* Validate that the While statement follows expected syntax, and that it contains an Expression. 
	* Defer validation of type to next phase.
	* @return A pointer to a While node containing the Expression and a pointer to its new associated block.
	*/
	While* _validateWhile();

	/**
	* Validate that the For statement follows expected syntax, and that it contains three Expression blocks.
	* Each Expression can be null to allow greater flexibility with loop usage.
	* Defer validation of each Expression block to the next phase.
	* @return  A pointer to a For node containing the three Expression's and a pointer to its new associated block.
	*/
	For* _validateFor();

	/**
	* Iterates up through the known tree to identify if the code is currently inside a loop block. Used by Break/Continue constructs.
	*/
	bool _isInLoop();

public:
	/**
	* Constructor for Validator class.
	* @param tags An std::list of TaggedLexeme's, containing the tag and line information gathered from parsing.
	*/
	Validator(taglist tags);

	/**
	* Parses the Lexeme stream to identify and construct Function Parameter objects for insertion into the Function class.
	* @return An std::list of FunctionParameter objects.
	*/
	std::list<FunctionParameter> validateFunctionParameters();

	/**
	* Parses the Lexeme Stream when the first tag is a Class or Type.
	* @return A boolean true if it parsed into a valid code tree.
	*/
	bool validateType();

	/**
	* Validate syntax starting from a class tag.
	*/
	bool validateClass();

	/**
	* Validate that the lexeme stream is a valid expression. Opens a new _activeClass pointer to store the new class data.
	* @return A pointer to a node of an Expression.
	*/
	Node* validateExpression();

	/**
	* Beginning point for validating the stream of Lexemes.
	*/
	bool validateSyntax();

	/**
	* Performs validation of opening and close braces
	*/
	bool validateSymbol();

	/**
	* Performs parsing of language statements e.g. IF, ELSE, FOR, WHILE, BREAK, CONTINUE. 
	*/
	bool validateStatement();

	// Update to use advanceToToken to move parse past minor non-blocking errors. e.g.
	// Type mismatch, unrecognised identifier, invalid keyword usage, unexpected symbol etc.
	//void advanceToToken(Token& token);
};

#endif