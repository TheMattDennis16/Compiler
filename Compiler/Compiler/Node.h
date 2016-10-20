#ifndef NODE_HH
#define NODE_HH

#include <string>
#include <memory>
#include <iostream>

#include "TokenTypes.h"


class Node
{
private:
	Node* _parent;
	int _line;
	int _tokenType;
public:
	Node(Node* parentPtr, int tokenType, int line);
	template <class T> void Throw(std::string err, T symbol);
};

template <class T>
inline void Node::Throw(std::string err, T symbol)
{
	std::cout << err << ". Near symbol '" << symbol << "' on line " << _line << std::endl;
}

#endif