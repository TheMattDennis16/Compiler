#include "Addition.h"

Addition::Addition(Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_isAlsoAssignment = false;
	_lOp = _rOp = nullptr;
}

Addition::Addition(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_isAlsoAssignment = isAssignment;
	_lOp = lOp;
	_rOp = rOp;
}