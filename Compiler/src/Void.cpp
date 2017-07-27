#include "DataTypes/Void.h"

Void::Void(Node::NodeDetails nodeDetails) : Type(nodeDetails)
{
	_id = TypeID::NEW_VOID;
	_size = 0;
	_typeName = "Void";
}
