#ifndef IF_NODE_HH
#define IF_NODE_HH

#include <list>

#include "Expr.h"
#include "Node.h"
#include "Block.h"

class If : public Node
{
private:
	Block* _parent;
	std::list<Node*> _elseStatements;
	Expr* _condition;

public:
	If(Block* parent, std::list<Node*> elseStatements, Expr* condition, NodeDetails details);
};

#endif