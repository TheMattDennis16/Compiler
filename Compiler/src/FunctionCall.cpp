#include "FunctionCall.h"

FunctionCall::FunctionCall(std::string fName, std::vector<FunctionParameterValue> fParamValues, Type* returnValue, NodeDetails nodeDetails)
	: Node(nodeDetails), _functionName(fName), _functionParameterValues(fParamValues), _returnValue(returnValue)
{
}

Type* FunctionCall::getReturnValue()
{
	return _returnValue;
}