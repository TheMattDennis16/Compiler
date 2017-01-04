
#ifndef CLASS_HH
#define CLASS_HH

#include <string>
#include <list>

#include "SymbolTable.h"
#include "ErrorCodes.h"
#include "Function.h"

class Class : public Type
{
private:
	std::string _name;
	std::list<Function*> _functions;
	SymbolTable _symbolTable;

	std::list<Function*> _findAllFunctionNameMatches(std::string name);

public:
	Class(std::string name);
	~Class();

	//Class level variables
	std::string getName();
	void setName(std::string name);

	//Function signature functions
	bool containsFunctionSignature(Function* function);
	bool doParamsMatchSignature(std::string fName, std::list<FunctionParameterValue> params);
	void addFunction(Function* function);

	bool isInSymbolTable(Symbol& symbol);
	void addToSymbolTable(Symbol& symbol);
};

#endif