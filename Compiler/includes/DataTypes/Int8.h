#ifndef INT_EIGHT_HH
#define INT_EIGHT_HH

#include "DataTypes/Type.h"

class Int8 : public Type
{
private:
public:
	/**
	* Default constructor for an 8-bit Integer.
	* @param the node details needed to store in the tree
	*/
	Int8(Node::NodeDetails nodeDetails);
};

#endif
