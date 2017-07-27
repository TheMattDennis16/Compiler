#include "Division.h"

Division::Division(Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_lOp = _rOp = nullptr;
}

Division::Division(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_isAlsoAssignment = isAssignment;
	_lOp = lOp;
	_rOp = rOp;
}