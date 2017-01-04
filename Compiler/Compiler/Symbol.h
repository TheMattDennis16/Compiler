#ifndef SYMBOL_HH
#define SYMBOL_HH

#include <string>

#include "Block.h"
#include "DataTypes\Type.h"

class Symbol
{
private:
	std::string _identifier;
	Block* _block;
	Type* _type;

public:
	Symbol(std::string name, Block* blockScope, Type* type);
	~Symbol();
	bool operator==(const Symbol& rhs);
};

#endif