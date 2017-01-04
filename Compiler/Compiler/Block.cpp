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

Node* Block::getParent()
{
	return _parent;
}

Block::Block(Node* parent)
{
	_parent = parent;
}