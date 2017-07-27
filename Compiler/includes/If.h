#ifndef IF_NODE_HH
#define IF_NODE_HH

#include <vector>

#include "Node.h"
#include "Block.h"

class If : public Node
{
private:
	Block* _child;
	std::vector<Node*> _elseStatements;
	Node* _condition;

public:
	/**
	* Constructor for the If Statement object.
	* @param child          The pointer to the Block object storing all the code for this 
	* @param elseStatements An std::list of Node pointers, each pointing to another associated If statement.
	* @param condition      The Expression which acts as the condition for this statement. 
	                        Must evaluate to a boolean value, checked in next phase.
	* @param details        The NodeDetails class storing other information about this Node.    
	*/
	If(Block* child, std::vector<Node*> elseStatements, Node* condition, NodeDetails details);
};

#endif