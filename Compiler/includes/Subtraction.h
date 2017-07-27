#ifndef SUBTRACTION_HH
#define SUBTRACTION_HH

#include "Node.h"

class Subtraction : public Node
{
private:
	bool _isAlsoAssignment;
	Node* _lOp;
	Node* _rOp;

public:
	Subtraction(Node::NodeDetails nodeDetails);
	Subtraction(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails);
};

#endif