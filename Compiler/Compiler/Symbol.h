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
	/**
	* Constructor for the Symbol class.
	* @param name       A string representation containing the Symbols identifier.
	* @param blockScope A pointer to the Block containing this Symbol. This therefore acts as the scope for the Symbol.
	* @param type       A pointer to a base class Type object, therefore allowing type checking later on as well as value storage.
	*/
	Symbol(std::string name, Block* blockScope, Type* type);

	/**
	* Destructor for the Symbol class.
	*/
	~Symbol();

	/**
	* Operator overloading for deep comparison of the Symbol class.
	* @param rhs Right-hand side operand for the operator.
	*/
	bool operator==(const Symbol& rhs);
};

#endif