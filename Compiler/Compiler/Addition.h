#ifndef ADDITION_H
#define ADDITION_H

#include "Node.h"

class Addition : public Node
{
private:
	bool _isAlsoAssignment;
	Node* _lOp;
	Node* _rOp;
public:
	Addition(Node::NodeDetails nodeDetails);
	Addition(bool isAssignment, Node* lOp, Node* rOp, Node::NodeDetails nodeDetails);
};

#endif 