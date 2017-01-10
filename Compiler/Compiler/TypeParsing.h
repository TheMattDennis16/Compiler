#ifndef TYPE_PARSING_HH
#define TYPE_PARSING_HH

#include "DataTypes\Type.h"
#include "DataTypes\Char.h"
#include "DataTypes\Void.h"

class TypeParsing
{
public:
	/**
	* Method for getting a pointer to a Type class, uses the string representation of the Token for identification. 
	* Raw types can be implemented here, with custom classes returning a Class pointer inheriting from Type.
	* @param typeName The string representation of the Token to have its type identified.
	* @return A pointer to a base class Type object.
	*/
	static Type* getType(std::string typeName)
	{
		if (typeName == "char")
			return new Char();
		else if (typeName == "void")
			return new Void();
	}
};

#endif