#ifndef AST_TESTS_CLASS_H
#define AST_TESTS_CLASS_H

#include "Validator.h"

class ASTTests : Validator
{
private:
	void setupTestData(taglist tags)
	{
		this->_resetPrivateData();
		this->addTags(tags);
	}

public:
	ASTTests()
	{}

	Node* validateEXPR(taglist tags)
	{
		setupTestData(tags);
		return this->_validateExpression();
	}

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

	std::vector<FunctionParameter> validateFUNCTIONPARAMETERS(taglist tags)
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

#endif
