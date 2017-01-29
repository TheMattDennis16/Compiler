#ifndef TYPE_HH
#define TYPE_HH

#include "../Node.h"

#include <string>

class Type : public Node
{
public:
	int _id;
	int _size;
	std::string _typeName;
	std::string _value;
	Type(Node::NodeDetails nodeDetails) : Node(nodeDetails)
	{
	}
};

enum TypeID
{
	NEW_CHAR,
	NEW_INT,
	NEW_DOUBLE,
	NEW_BOOL,
	NEW_CLASS,
	NEW_VOID
};

#endif