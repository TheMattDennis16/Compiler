#ifndef FOR_HH
#define FOR_HH

#include "Node.h"
#include "Expr.h"
#include "Block.h"

class For : public Node
{
private:
	Expr* _declaration;
	Expr* _condition;
	Expr* _result;
	Block* _block;

public:
	For(Expr* declaration, Expr* condition, Expr* result, Block* child, NodeDetails nodeDetails);
};

#endif