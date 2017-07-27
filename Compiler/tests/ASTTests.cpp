#include "TestingTools.h"
#include "ASTTestsClass.h"

#include <vector>
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ast_tests

/*
 * Isolate tag creation by doing it manually. No point relying on the LexicalAnalyser.
 */
BOOST_AUTO_TEST_SUITE(AST_Tests)

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
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::TYPE, "int8"), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "a"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Assignment expected(
		new Int8(Node::NodeDetails(nullptr,0,0)),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, TokenTypes::OPERATOR, 1)
		);

	ASTTests testClass;
	printf("qwe");
	Node* resultNode = testClass.validateTYPE(lexemes);
	printf("qwe");
	Assignment result = dynamic_cast<Assignment&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");;
}

BOOST_AUTO_TEST_CASE(Addition_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1)
	};

	Addition expected(
		false,
		new IntLiteral(1),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 0));

	ASTTests testClass;
	Node* resultNode = testClass.validateTYPE(lexemes);
	Addition result = dynamic_cast<Addition&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Addition_Assignment_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Addition expected(
		true,
		new Int8(Node::NodeDetails(nullptr, 0, 0)),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 0));

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Addition result = dynamic_cast<Addition&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Addition_Assignment_Nested_Expression)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+="), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, "("), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ")"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)

	};

	Addition expected(
		true,
		new Int8(Node::NodeDetails(nullptr, 0, 0)),
		new Addition(false,
			new IntLiteral(1),
			new IntLiteral(1),
			Node::NodeDetails(nullptr, 0, 0)
			),
		Node::NodeDetails(nullptr, 0, 0));

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Addition result = dynamic_cast<Addition&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Double_Nested_Expression)
{
	//test = ((1+2) + (3+4));
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "="), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, "("), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, "("), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "2"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ")"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, "("), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "3"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "4"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ")"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ")"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Assignment expected(
		new Int8(Node::NodeDetails(nullptr, 0, 1)),
		new Addition(false,
			new Addition(
				false,
				new IntLiteral(1),
				new IntLiteral(2),
				Node::NodeDetails(nullptr, 0, 1)
				),
			new Addition(
				false,
				new IntLiteral(3),
				new IntLiteral(4),
				Node::NodeDetails(nullptr, 0, 1)
				),
			Node::NodeDetails(nullptr, 0, 1)
		),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Assignment result = dynamic_cast<Assignment&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Subtraction_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "-"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Subtraction expected(
		false,
		new IntLiteral(1),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Subtraction result = dynamic_cast<Subtraction&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Subtraction_Assignment_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "-="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Subtraction expected(
		true,
		new Int8(Node::NodeDetails(nullptr, 0, 1)),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Subtraction result = dynamic_cast<Subtraction&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Division_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "/"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Division expected(
		false,
		new IntLiteral(1),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateTYPE(lexemes);
	Division result = dynamic_cast<Division&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Division_Assignment_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "/="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Division expected(
		true,
		new Int8(Node::NodeDetails(nullptr, 0, 1)),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateTYPE(lexemes);
	Division result = dynamic_cast<Division&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Multiply_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "*"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Multiplication expected(
		false,
		new IntLiteral(1),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateTYPE(lexemes);
	Multiplication result = dynamic_cast<Multiplication&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Multiply_Assignment_Operator)
{
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "*="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Multiplication expected(
		true,
		new Int8(Node::NodeDetails(nullptr, 0, 1)),
		new IntLiteral(1),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateTYPE(lexemes);
	Multiplication result = dynamic_cast<Multiplication&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Order_Of_Operations_One)
{
	//test = 2 * (a + (b / 10) - 50)
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "2"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "*"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, "("), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "a"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, "("), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "b"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "/"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "10"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ")"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "-"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "50"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ")"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Assignment expected(
		new Int8(Node::NodeDetails(nullptr, 0, 1)),
		new Multiplication(
			false,
			new IntLiteral(2),
			new Subtraction(
				false,
				new Addition(
					false,
					new Int8(Node::NodeDetails(nullptr, 0, 1)),
					new Division(
						false,
						new Int8(Node::NodeDetails(nullptr, 0, 1)),
						new IntLiteral(10),
						Node::NodeDetails(nullptr, 0, 1)
						),
					Node::NodeDetails(nullptr, 0, 1)
					),
				new IntLiteral(50),
				Node::NodeDetails(nullptr, 0, 1)
				),
			Node::NodeDetails(nullptr, 0, 1)
			),
		Node::NodeDetails(nullptr, 0, 1));

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Assignment result = dynamic_cast<Assignment&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Order_Of_Operations_Two)
{
	//test = a / b * c + d - e;
	//test = 8 / 2 * 2 + 3 - 8
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "="), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "8"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "/"), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "2"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "*"), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "2"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "3"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "-"), 1),
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "8"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Assignment expected(
		new Int8(Node::NodeDetails(nullptr, 0, 1)),

		new Subtraction(
			false,
			new Addition(
				false,
				new Multiplication(
					false,
					new Division(
						false,
						new IntLiteral(8), //a
						new IntLiteral(2), //b
						Node::NodeDetails(nullptr, 0, 1)
					),
					new IntLiteral(2),     //c
					Node::NodeDetails(nullptr, 0, 1)
				),
				new IntLiteral(3),
				Node::NodeDetails(nullptr, 0, 1)
			),
			new IntLiteral(8),
			Node::NodeDetails(nullptr, 0, 1)
		),
		Node::NodeDetails(nullptr, 0, 1)
	);

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Assignment result = dynamic_cast<Assignment&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Order_Of_Operations_Three)
{
	//test = 1 + 2 - 3 * 8 / 4;
	//test = a + b - c * d / e;
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "2"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "-"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "3"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "*"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "8"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "/"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "4"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Assignment expected(
		new Int8(Node::NodeDetails(nullptr, 0, 1)),
		new Subtraction(
			false,
			new Addition(
				false,
				new IntLiteral(1),
				new IntLiteral(2),
				Node::NodeDetails(nullptr, 0, 1)
			),
			new Multiplication(
				false,
				new IntLiteral(3),
				new Division(
					false,
					new IntLiteral(8),
					new IntLiteral(4),
					Node::NodeDetails(nullptr, 0, 1)
				),
				Node::NodeDetails(nullptr, 0, 1)
			),
			Node::NodeDetails(nullptr, 0, 1)
		),
		Node::NodeDetails(nullptr, 0, 1)
	);

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Assignment result = dynamic_cast<Assignment&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Order_Of_Operations_Four)
{
	//test = 1 * 2 - 3 / 8 + 4;
	std::vector<TaggedLexeme> lexemes = {
		TaggedLexeme(Token(TokenTypes::IDENTIFIER, "test"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "="), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "1"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "*"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "2"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "-"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "3"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "/"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "8"), 1),
		TaggedLexeme(Token(TokenTypes::OPERATOR, "+"), 1),
		TaggedLexeme(Token(TokenTypes::VAR_VALUE, "4"), 1),
		TaggedLexeme(Token(TokenTypes::SYMBOL, ";"), 1)
	};

	Assignment expected(
		new Int8(Node::NodeDetails(nullptr, 0, 1)),
		new Addition(
			false,
			new Subtraction(
				false,
				new Multiplication(
					false,
					new IntLiteral(1),
					new IntLiteral(2),
					Node::NodeDetails(nullptr, 0, 1)),
				new Division(
					false,
					new IntLiteral(3),
					new IntLiteral(8),
					Node::NodeDetails(nullptr, 0, 1)),
				Node::NodeDetails(nullptr, 0, 1)
			),
			new IntLiteral(4),
			Node::NodeDetails(nullptr, 0, 1)
		),
		Node::NodeDetails(nullptr , 0, 1)
	);

	ASTTests testClass;
	Node* resultNode = testClass.validateEXPR(lexemes);
	Assignment result = dynamic_cast<Assignment&>(*resultNode);
	BOOST_REQUIRE_EQUAL(result == expected, true);
	printf("\n\n");
}

BOOST_AUTO_TEST_SUITE_END()
