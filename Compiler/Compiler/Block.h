#ifndef BLOCK_HH
#define BLOCK_HH

#include "Node.h"

#include <list>

typedef std::list<Node*>::iterator iterator;

class Block : public Node
{
private:
	std::list<Node*> _nodes;
	Node* _parent;

public:
	bool isClosed;

	Block(Node* parent);
	iterator getIterator();
	iterator getIteratorEnd();
	void addNode(Node* node);
	Node* getParent();
};

#endif