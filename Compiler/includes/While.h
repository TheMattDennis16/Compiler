#ifndef WHILE_HH
#define WHILE_HH

#include "Node.h"
#include "Block.h"

class While : public Node
{
private:
	Node* _expression;
	Block* _block;

public:
	/**
	* Constructor for the While class. Inherits from a standard Node.
	* @param expression A pointer to the associated Expression object for this construct.
	* @param block      A pointer to the block associated with this construct.
	*/
	While(Node* expression, Block* block, Node::NodeDetails nodeDetails);
};

#endif