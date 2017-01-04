#include "If.h"

If::If(Block* parent, std::list<Node*> elseStatements, Expr* condition, NodeDetails details) : Node(details)
{
	_parent = parent;
	_elseStatements = elseStatements;
	_condition = condition;
}