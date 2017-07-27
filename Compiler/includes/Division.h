#ifndef DIVISION_HH
#define DIVSION_HH

#include "Node.h"

class Division : public Node
{
private:
	bool _isAlsoAssignment;
	Node* _lOp;
	Node* _rOp;

public:
	Division(Node::NodeDetails nodeDetails);
	Division(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails);
};

#endif
