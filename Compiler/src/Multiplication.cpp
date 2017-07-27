#include "Multiplication.h"

Multiplication::Multiplication(Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_lOp = _rOp = nullptr;
}

Multiplication::Multiplication(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_isAlsoAssignment = isAssignment;
	_lOp = lOp;
	_rOp = rOp;
}