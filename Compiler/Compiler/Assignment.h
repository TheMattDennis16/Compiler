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
	* @param lOp Left operand for the assignment operator, either a Class as a type or a raw Type.
	* @param rOp Right operand for the assignment operator. Must be a valid expression. Check type later in tree validation step.
	* @param nodeDetails Details for the Node baseclass.
	*/
	Assignment(Type* lOp, Node* rOp, NodeDetails nodeDetails);

	/**
	* Deep comparison operator for the Assignment node
	* @param right The right (other) node in the assignment expression.
	* @return True if the nodes have matching values
	*/
	bool operator==(const Assignment& right);
};

#endif