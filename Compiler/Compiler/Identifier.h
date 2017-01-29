#ifndef IDENTIFIER_HH
#define IDENTIFIER_HH

#include <string>
#include "Node.h"

//Not the same as a Symbol, Symbols go in the Symbol table. An identifier is a tree-member usage of a Symbol.
class Identifier : Node
{
private:
	std::string identifier;

public:
	Identifier(std::string identifier, NodeDetails nodeDetails)
};

#endif