#define BOOST_TEST_MODULE example

#include <boost/test/included/unit_test.hpp>
#include "../Compiler/Compiler.h"
#include "TestingTools.h"

BOOST_AUTO_TEST_SUITE(Lexer_Tests)

BOOST_AUTO_TEST_CASE(Single_Line_Variable)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/single_line_variable.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "int8,a,=,1,;");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Double_Line_Variable)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/double_line_variable.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "int32,a,=,2,;");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Function_With_Params)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/function_with_params.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "void,test,(,int8,a,,,char,b,),{,}");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(If_Statement)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/if.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "if,(,a,==,b,),{,}");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(While_Statement)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/while.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "while,(,a,==,b,),{,}");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Index_Access)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/index_access.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "int8,a,=,numbers,[,1,],;");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Single_Operator)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/single_operator.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "int8,a,=,1,+,2,;");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Compound_Operator)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/compound_operator.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "int16,test,=,6,;,test,+=,7,;");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(String_Literal)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/string_literals.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "char,[,],charArr,=,\",abcdefg,\",;");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Char)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/char.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, "char,testing,=,\',a,\',;");
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Char_In_String)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/char_in_string.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	std::string expected = "char,[,],str,=,\",My name is \'Matt\',\",;";
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, expected);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Full_Function_Test)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/full_test.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	std::string expected = "int8,doMath,(,double,a,,,double,b,),{,char,[,],veryLongName,=,\",Testing,\",;,for,(,int8,i,=,0,;,i,<,5,;,i,++,),{,},int8,result,=,2,*,(,b,+,3,),;,double,retVal,=,0,;,if,(,result,==,15,),retVal,=,result,;,else,{,retVal,=,1000,;,},return,retVal,;,}";
	sresult = sresult.substr(0, sresult.size() - 1);
	for (int i = 0; i < sresult.size(); i++)
	{
		if (sresult.at(i) != expected.at(i))
		{
			std::string err = std::string("") + sresult.at(i) + std::string("    ") + expected.at(i) + "\r\n";
			printf(err.c_str());
		}
	}
	BOOST_REQUIRE_EQUAL(sresult, expected);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Class)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/class.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	std::string expected = "class,Test,{,}";
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, expected);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Include_Class)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/include_class.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	std::string expected = "include,\",file.a,\",;";
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, expected);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Single_Line_Comment)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/single_line_comment.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	std::string expected = "";
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, expected);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Comment_With_Expr)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/comment_with_expr.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	std::string expected = "int8,a,=,1,;";
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, expected);
	printf("\n\n");
}

BOOST_AUTO_TEST_CASE(Int_Types)
{
	Compiler compiler;
	compiler.parseFile("TestFiles/int_types.a");
	auto result = compiler.getLexerOutput();
	std::string sresult = TestingTools::lexToString(result);
	std::string expected = "int8,a,=,1,;,int16,b,=,2,;,int32,c,=,3,;,int64,d,=,4,;";
	sresult = sresult.substr(0, sresult.size() - 1);
	BOOST_REQUIRE_EQUAL(sresult, expected);
	printf("\n\n");
}

BOOST_AUTO_TEST_SUITE_END()