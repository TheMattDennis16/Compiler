#include "If.h"

If::If(Block* child, std::vector<Node*> elseStatements, Node* condition, NodeDetails details) : Node(details)
{
	_child = child;
	_elseStatements = elseStatements;
	_condition = condition;
}