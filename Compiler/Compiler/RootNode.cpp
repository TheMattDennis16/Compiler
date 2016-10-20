#include "RootNode.h"

void RootNode::addFunction(std::string fNameWithScope, Function* function)
{
	if (getFunctionSignature(fNameWithScope) == nullptr)
	{
		std::cerr << ErrorCodes::FUNCTION_NAME_DEFINED_IN_SCOPE << std::endl;
	}
	else _functions.insert(std::pair<std::string, Function*>(function->getName(), function));
}

Function* RootNode::getFunctionSignature(std::string functionWithScope)
{
	if (_functions.find(functionWithScope) == _functions.end())
		return nullptr;
	return _functions.at(functionWithScope);
}