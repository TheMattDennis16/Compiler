#ifndef VALIDATOR_HH
#define VALIDATOR_HH

#include "LexicalAnalyser.h"
#include "RootNode.h"
#include "TokenTypes.h"
#include "FileHandling.h"
#include "TypeParsing.h"

#include "Node.h"
#include "Function.h"
#include "Assignment.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Division.h"
#include "Multiplication.h"
#include "While.h"
#include "For.h"
#include "If.h"
#include "Class.h"
#include "Break.h"
#include "Continue.h"

#include "DataTypes/Bool.h"
#include "DataTypes/Int8.h"
#include "DataTypes/IntLiteral.h"

#include <vector>

typedef std::vector<TaggedLexeme> taglist;
typedef std::vector<TaggedLexeme>::iterator tagIt;

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

protected:
	/*
	* Increments the iterator to load the next available TaggedLexeme. This updates the private _it Iterator for the tag std::vector
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

	/**
	* Parses the Lexeme stream to identify and construct Function Parameter objects for insertion into the Function class.
	* @return An std::vector of FunctionParameter objects.
	*/
	std::vector<FunctionParameter> _validateFunctionParameters();

	/**
	* Parses the Lexeme Stream when the first tag is a Class or Type.
	* @return A generic base class pointer of a range of different types containing the subtree for the Node type.
	*/
	Node* _validateType();

	/**
	* Validate syntax starting from a class tag.
	* @return a pointer to the new Class object.
	*/
	Class* _validateClass();

	/**
	* Validate that the lexeme stream is a valid expression. Opens a new _activeClass pointer to store the new class data.
	* @return A pointer to a node of an Expression.
	*/
	Node* _validateExpression();

	/**
	* Beginning point for validating the stream of Lexemes.
	*/
	bool _validateSyntax();

	/**
	* Performs validation of opening and close braces
	*/
	bool _validateSymbol();

	/**
	* Performs parsing of language statements e.g. IF, ELSE, FOR, WHILE, BREAK, CONTINUE.
	*/
	Node* _validateStatement();

	/**
	* Perform the parsing for operators.
	* @param stack Accept the current stack object to continue where previously left off.
	*/
	Node* _validateOperator(std::vector<TaggedLexeme> stack);

	// Update to use advanceToToken to move parse past minor non-blocking errors. e.g.
	// Type mismatch, unrecognised identifier, invalid keyword usage, unexpected symbol etc.
	//void _advanceToToken(Token& token);

	/**
	* Resets the private data back to default state so that the class may be reused from a blank state.
	*/
	void _resetPrivateData();

public:

	/**
	* Default constructor for the Validator class.
	*/
	Validator();

	/**
	* Constructor for Validator class.
	* @param tags An std::vector of TaggedLexeme's, containing the tag and line information gathered from parsing.
	*/
	Validator(taglist tags);

	/**
	* Method to call for building of the Abstract Syntax Tree.
	*/
	bool buildTree();

	/**
	* Overload method which uses the specified taglist rather than any previously defined one.
	* param tags An std::vector of tags to build the AST from.
	* return true if the tree was built successfully, false if it was not.
	*/
	bool buildTree(taglist tags);

	/**
	* Public method to allow tags to be added
	* param tags an std::vector of tags to be used later on should a buildTree method be called.
	*/
	void addTags(taglist tags);
};

#endif
