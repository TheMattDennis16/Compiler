#ifndef CHAR_HH
#define CHAR_HH

#include "Type.h"

class Char : public Type
{
private:
public:
	/**
	* Default constructor for the Character type
	* @param The details needed for storing this node in the tree
	*/
	Char(Node::NodeDetails nodeDetails);
};

#endif