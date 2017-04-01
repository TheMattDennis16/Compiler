#include "If.h"

If::If(Block* child, std::list<Node*> elseStatements, Node* condition, NodeDetails details) : Node(details)
{
	_child = child;
	_elseStatements = elseStatements;
	_condition = condition;
}