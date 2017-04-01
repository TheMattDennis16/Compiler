#ifndef FOR_HH
#define FOR_HH

#include "Node.h"
#include "Block.h"

class For : public Node
{
private:
	Node* _declaration;
	Node* _condition;
	Node* _result;
	Block* _block;

public:
	For(Node* declaration, Node* condition, Node* result, Block* child, NodeDetails nodeDetails);
};

#endif