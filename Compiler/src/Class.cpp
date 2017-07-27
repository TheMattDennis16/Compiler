#include "Class.h"

Class::Class(std::string name, Node::NodeDetails nodeDetails) : _name(name), Type(nodeDetails)
{
	_typeName = name;
	_id = TypeID::NEW_CLASS;
	_size = 0;
}

Class::~Class()
{
	//Call for the deletion of each element.
	for (Function* fptr : _functions)
	{
		delete fptr;
	}
}

std::string Class::getName()
{
	return _name;
}


void Class::setName(std::string name)
{
	_name = name;
};

std::vector<Function*> Class::_findAllFunctionNameMatches(std::string name)
{
	std::vector<Function*> results;
	for (Function* fptr : _functions)
	{
		if (name == fptr->getName())
			results.push_back(fptr);
	}
	return results;
}

FunctionCall Class::callFunction(std::string fName, std::vector<FunctionParameterValue> params)
{
	return FunctionCall("", std::vector<FunctionParameterValue>{}, nullptr, Node::NodeDetails(nullptr, 0, 0));
}

void Class::addFunction(Function* function)
{
	if (containsFunctionSignature(function) == true)
	{
		//std::cerr << ErrorCodes::FUNCTION_NAME_DEFINED_IN_SCOPE << std::endl;
	}
	else _functions.push_back(function);
}

bool Class::containsFunctionSignature(Function* function)
{
	for (Function* fptr : _functions)
	{
		if (*fptr == *function) 
		{
			return true;
		}
	}
	return false;
}

Function* Class::doParamsMatchSignature(std::string fName, std::vector<FunctionParameterValue> params)
{
	std::vector<Function*> functions = _findAllFunctionNameMatches(fName);

	for (Function* fptr : functions)
	{
		std::vector<FunctionParameter> fparams = fptr->getParameters();
		if (params.size() != fparams.size())
			continue;

		bool isMatch = true;
		auto paramValsIt = params.begin();
		for (FunctionParameter param : fparams)
		{
			if (param._type != (*paramValsIt)._type)
				paramValsIt++;
			else
			{
				isMatch = false;
				break;
			}
		}

		if (isMatch)
		{
			return fptr;
		}
	}
	return nullptr;
}

bool Class::isInSymbolTable(Symbol& symbol)
{
	return _symbolTable.containsSymbol(symbol);
}

void Class::addToSymbolTable(Symbol& symbol)
{
	_symbolTable.addSymbol(symbol);
}