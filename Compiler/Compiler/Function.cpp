#include "Function.h"

Function::Function(std::list<FunctionParameter>& params, int line, std::string name) : Node(nullptr, TokenTypes::IDENTIFIER, line)
{

}

std::string Function::getName()
{
	return std::string("to be implemented");
}