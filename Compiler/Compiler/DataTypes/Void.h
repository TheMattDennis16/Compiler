#ifndef VOID_HH
#define VOID_HH

#include "Type.h"

class Void : public Type
{
private:
public:
	/**
	* Default constructor for the Void return type.
	* @param nodeDetails the details for this node needed for easier tree traversal
	*/
	Void(Node::NodeDetails nodeDetails);
};

#endif