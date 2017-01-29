#define BOOST_TEST_MODULE ast_tests
#include <boost/test/included/unit_test.hpp>
#include "../Compiler/Validator.h"
#include "TestingTools.h"
#include <list>

class ASTTests : Validator
{
private:
	void setupTestData(taglist tags)
	{
		this->_resetPrivateData();
		this->addTags(tags);
	}

public:
	ASTTests() {}

	If* validateIF(taglist tags)
	{
		setupTestData(tags);
		return this->_validateIf();
	}

	For* validatorFOR(taglist tags)
	{
		setupTestData(tags);
		return this->_validateFor();
	}

	While* validateWHILE(taglist tags)
	{
		setupTestData(tags);
		return this->_validateWhile();
	}

	Node* validateTYPE(taglist tags)
	{
		setupTestData(tags);
		return this->_validateType();
	}

	std::list<FunctionParameter> validateFUNCTIONPARAMETERS(taglist tags)
	{
		setupTestData(tags);
		return this->_validateFunctionParameters();
	}

	bool isInLOOP(taglist tags)
	{
		setupTestData(tags);
		return this->_isInLoop();
	}

};


/*
 * Isolate tag creation by doing it manually. No point relying on the LexicalAnalyser.
 */
BOOST_AUTO_TEST_SUITE(Lexer_Tests)

BOOST_AUTO_TEST_CASE(Assignment_Operator)
{
	/*
	 * test the _validateExpr method, should return a tree of:
	 * [TYPE] [IDENTIFIER] [OP] [EXPR] ;
	 * which would be a tree of:
	 *                     =
	 *                    / \
	 *  {Type, Identifier}   {value}
	 */
	std::list<TaggedLexeme> lexemes = { 
		TaggedLexeme(Token(TokenTypes::TYPE, "int"), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "a"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1)
	};

	Assignment expected(
		nullptr,
		new Int8(),
		new Expr(),
		NodeDetails(nullptr, TokenTypes::OPERATOR, 1)
		);

	ASTTests testClass;
	testClass.addTags(lexemes);


	BOOST_REQUIRE_EQUAL(expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_SUITE_END()