#ifndef ROOT_NODE_HH
#define ROOT_NODE_HH

#include <string>
#include <unordered_map>
#include <iostream>
#include <utility>

#include "ErrorCodes.h"
#include "Function.h"

class RootNode
{
private:
	std::unordered_map<std::string, Function*> _functions;

public:
	void addFunction(std::string fNameWithScope, Function* function);
	Function* getFunctionSignature(std::string functionWithScope);
};

#endif