#ifndef ASSIGNMENT_HH
#define ASSIGNMENT_HH

#include "Node.h"
#include "DataTypes\Type.h"
#include "Block.h"

class Assignment : public Node
{
private:
	Block* _parent; //Scope for variable
	Node* _leftOperand; //Can be either a Declaration instance (aka a pair of {Type | Identifier}) or an Identifier symbol.
	Node* _rightOperand; //Must be valid expression.

public:
	/**
	* Assignment operator constructor.
	* @param p   Pointer to the parent block.
	* @param lOp Left operand for the assignment operator, either a Class as a type or a raw Type.
	* @param rOp Right operand for the assignment operator. Must be a valid expression. Check type later in tree validation step.
	* @param nodeDetails Details for the Node baseclass.
	*/
	Assignment(Block* p, Type* lOp, Node* rOp, NodeDetails nodeDetails);
};

#endif