#ifndef TYPE_PARSING_HH
#define TYPE_PARSING_HH

#include "DataTypes\Type.h"
#include "DataTypes\Char.h"
#include "DataTypes\Void.h"

class TypeParsing
{
public:
	static Type* getType(std::string typeName)
	{
		if (typeName == "char")
			return new Char();
		else if (typeName == "void")
			return new Void();
	}
};

#endif