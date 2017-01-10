#ifndef ASSIGNMENT_HH
#define ASSIGNMENT_HH

#include "Node.h"
#include "DataTypes\Type.h"
#include "Block.h"

class Assignment : public Node
{
private:
	Block* _parent; //Scope for variable
	Node* _leftOperand;
	Node* _rightOperand; //Must be valid expression.

public:
	/**
	* Assignment operator constructor.
	* @param p   Pointer to the parent block.
	* @param lOp Left operand for the assignment operator, either a Class as a type or a raw Type.
	* @param rOp Right operand for the assignment operator. Must be a valid expression. Check type later in tree validation step.
	*/
	Assignment(Block* p, Type* lOp, Node* rOp);
};

#endif