#ifndef FUNCTION_CALL_HH
#define FUNCTION_CALL_HH

#include <string>
#include <list>

#include "DataTypes\Type.h"
#include "Function.h"
#include "Node.h"

class FunctionCall : public Node
{
private:
	std::string _functionName;
	std::list<FunctionParameterValue> _functionParameterValues;
	Type* _returnValue;

public:
	/**
	* Constructor for the FunctionCall object.
	* @param fname        The function name of the object to call.
	* @param fParamValues The parameter values of the call.
	* @param returnValue  The return value type.
	* @param nodeDetails  The NodeDetails needed to setup the base class.
	*/
	FunctionCall(std::string fName, std::list<FunctionParameterValue> fParamValues, Type* returnValue, NodeDetails nodeDetails);
	
	/**
	* Getter method for the return value of the function.
	* @return A pointer to a Type object. The Type object contains the value of a raw type, while also being the storage method for a Class object.
	*/
	Type* getReturnValue();
};

#endif