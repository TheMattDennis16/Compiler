#include "IntLiteral.h"

IntLiteral::IntLiteral() : Node(Node::NodeDetails(nullptr, 0, 0))
{
	_intValue = 0;
}

IntLiteral::IntLiteral(long long value) : Node(Node::NodeDetails(nullptr, 0, 0))
{
	_intValue = value;
}

void IntLiteral::setValue(long long value)
{
	_intValue = value;
}

long long IntLiteral::getValue()
{
	return _intValue;
}