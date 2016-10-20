#include "Node.h"

Node::Node(Node* parentPtr, int tokenType, int line)
{
	_parent = parentPtr;
	_tokenType = tokenType;
	_line = line;
}