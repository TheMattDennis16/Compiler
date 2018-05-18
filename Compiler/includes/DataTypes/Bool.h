#ifndef BOOL_HH
#define BOOL_HH

#include "DataTypes/Type.h"

class Bool : public Type
{
private:
public:
	/**
	* Default constructor for a boolean value.
	* @param the node details needed to store in the tree
	*/
	Bool(Node::NodeDetails nodeDetails);
};

#endif
