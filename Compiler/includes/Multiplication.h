#ifndef MULTIPLY_HH
#define MULTIPLY_HH

#include "Node.h"

class Multiplication : public Node
{
private:
	bool _isAlsoAssignment;
	Node* _lOp;
	Node* _rOp;

public:
	Multiplication(Node::NodeDetails nodeDetails);
	Multiplication(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails);
};

#endif