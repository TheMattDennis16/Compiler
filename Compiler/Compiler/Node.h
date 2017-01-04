#ifndef NODE_HH
#define NODE_HH

#include <string>
#include <memory>
#include <iostream>

#include "TokenTypes.h"

class Node
{
private:
	NodeDetails _details;
	virtual void stub();

public:
	Node(NodeDetails details);
};

class NodeDetails
{
private:
public:
	Node* _parent;
	int _line;
	int _tokenType;
	NodeDetails(Node* parentPtr, int tokenType, int line) : _parent(parentPtr), _tokenType(tokenType), _line(line)
	{
	}
};


#endif