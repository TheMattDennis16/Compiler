#ifndef ASSIGNMENT_HH
#define ASSIGNMENT_HH

#include "Node.h"
#include "DataTypes\Type.h"
#include "Block.h"

class Assignment : public Node
{
private:
	//Type contains value information.
	Node _type; //Type or Class
	Block* _block; //Scope for variable
	std::string _identifier;


public:
	Assignment(Node type, Block* block, std::string identifier);
};

#endif