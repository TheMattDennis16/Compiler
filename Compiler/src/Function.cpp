#include "Function.h"

Function::Function(std::vector<FunctionParameter> params, std::string name, NodeDetails details) : Node(NodeDetails(details._parent, TokenTypes::IDENTIFIER, details._line))
{
	_block = new Block(Node::NodeDetails(this, 0, details._line));
	_params = params;
	_name = name;
}

Function::~Function()
{
	delete _block;
}

std::string Function::getName()
{
	return _name;
}

void Function::addParameter(FunctionParameter param)
{
	_params.push_back(param);
}

Block* Function::getBlock()
{
	return _block;
}

std::vector<FunctionParameter> Function::getParameters() const
{
	return _params;
}

bool Function::operator==(const Function& rhs)
{
	// Support for operator overloading. Therefore:
	// Allow same name but different parameters.
	// Allow different name but same parameters.
//	if (_params == rhs._params && _name == rhs._name)
//		return true;
	return false;
}

void Function::setBlock(Block* setBlock)
{
	_block = setBlock;
}