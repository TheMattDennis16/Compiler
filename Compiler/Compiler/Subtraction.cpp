#include "Subtraction.h"

Subtraction::Subtraction(Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_lOp = _rOp = nullptr;
}

Subtraction::Subtraction(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_isAlsoAssignment = isAssignment;
	_lOp = lOp;
	_rOp = rOp;
}