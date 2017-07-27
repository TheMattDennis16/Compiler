#include "Symbol.h"

Symbol::Symbol(std::string name, Block* blockScope, Type* type)
{
	_identifier = name;
	_block = blockScope;
	_type = type;
}

Symbol::~Symbol()
{
	delete _block;
	delete _type;
}

bool Symbol::operator==(const Symbol& rhs)
{
	//Pointer comparisons aren't ideal, need to define comparison operators for new classes.
	return (_identifier == rhs._identifier && _block == rhs._block && _type == rhs._type);
}