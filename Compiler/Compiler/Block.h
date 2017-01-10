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

	/**
	* Constructor for the Block class.
	* @param parent This pointer is set to the Node of the parent Object in the tree.
	*/
	Block(Node* parent);

	/**
	* Returns the beginning iterator of the nodes in the block.
	* @return Returns a begin() iterator for an std::list
	*/
	iterator getIterator();

	/**
	* Returns the end iterator of the nodes in the block.
	* @return Returns the end() iterator for an std::list
	*/
	iterator getIteratorEnd();

	/**
	* Adds a node to the current list of Blocks. Used to store any child code contained within this scope.
	* @param node The node to be added to the std::list of Nodes.
	*/
	void addNode(Node* node);

	/**
	* Gets the parent node of this block in the source tree.
	* @return Returns a pointer to the parent of this node in the source tree.
	*/
	Node* getParent();
};

#endif