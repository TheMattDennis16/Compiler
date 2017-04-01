#include "Assignment.h"

Assignment::Assignment(Type* lOp, Node* rOp, NodeDetails nodeDetails) : Node(nodeDetails)
{
	_leftOperand = lOp;
	_rightOperand = rOp;
}

bool Assignment::operator==(const Assignment& right)
{
	return *this->_leftOperand == *right._leftOperand
		&& *this->_rightOperand == *right._rightOperand
		&& *this->_parent == *right._parent;
}