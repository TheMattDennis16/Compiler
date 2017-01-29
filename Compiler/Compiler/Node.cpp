#include "Node.h"

Node::Node(NodeDetails details) : _details(details)
{
}

Node* Node::getParent()
{
	return _details._parent;
}