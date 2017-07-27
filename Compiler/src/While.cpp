#include "While.h"

While::While(Node* expression, Block* block, Node::NodeDetails nodeDetails) : Node(nodeDetails)
{
	_expression = expression;
	_block = block;
}