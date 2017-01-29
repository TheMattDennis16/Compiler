#include "Block.h"

iterator Block::getIterator()
{
	return _nodes.begin();
}

iterator Block::getIteratorEnd()
{
	return _nodes.end();
}

void Block::addNode(Node* node)
{
	_nodes.push_back(node);
}

Block::Block(Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
}