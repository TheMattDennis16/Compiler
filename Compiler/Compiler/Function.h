#ifndef FUNCTION_HH
#define FUNCTION_HH

#include <string>
#include <list>

#include "DataTypes\Type.h"
#include "Node.h"
#include "DataTypes\Type.h"

class FunctionParameter
{
	//Defer template type definition to ensure runtime behaviour.
public:
	Type _type;
	std::string _name;
	
	FunctionParameter(Type type, std::string name)
	{
		_type = type;
		_name = name;
	}
};

class Function : Node
{
private:
	Node* _parent;
	std::list<FunctionParameter> _params;
	std::list<Node*> _startNodes;
	std::string _nameIncludingScope;
	int _line;

public:
	std::string getName();
	Function(
		std::list<FunctionParameter>& params, 
		int line,
		std::string name
		);
};

#endif