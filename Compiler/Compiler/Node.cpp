#include "Node.h"

Node::Node(NodeDetails details) : _details(details)
{
}

Node* Node::getParent()
{
	return _details._parent;
}

void Node::setNodeDetails(NodeDetails details)
{
	_details = details;
}

bool Node::operator==(const Node& right)
{
	//Don't try to compare parent Node* types. You'll just enter a recursively deep loop going up the tree.
	return this->_details._line == right._details._line
		&& this->_details._tokenType == right._details._tokenType;
}
