#ifndef DECLARATION_HH
#define DECLARATION_HH

#include "Node.h"
#include "Identifier.h"
#include "DataTypes\Type.h"

class Declaration : Node 
{
private:
	Type* _type;
	Identifier* _identifier;

public:
	Declaration(Type* type, Identifier* identifier, NodeDetails nodeDetails);
};

#endif