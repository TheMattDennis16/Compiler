#include "DataTypes/Char.h"

Char::Char(Node::NodeDetails nodeDetails) : Type(nodeDetails)
{
	_id = TypeID::NEW_CHAR;
	_size = 1;
	_typeName = "Char";
}
