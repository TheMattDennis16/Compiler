#ifndef TYPE_PARSING_HH
#define TYPE_PARSING_HH

#include "DataTypes/Type.h"
#include "DataTypes/Char.h"
#include "DataTypes/Void.h"
#include "DataTypes/Int8.h"

class TypeParsing
{
public:
	/**
	* Method for getting a pointer to a Type class, uses the string representation of the Token for identification. 
	* Raw types can be implemented here, with custom classes returning a Class pointer inheriting from Type.
	* @param typeName The string representation of the Token to have its type identified.
	* @return A pointer to a base class Type object.
	*/
	static Type* getType(std::string typeName, Node::NodeDetails nodeDetails)
	{
		//Convert to switch at some point.
		if (typeName == "char")
			return new Char(nodeDetails);
		else if (typeName == "void")
			return new Void(nodeDetails);
		else if (typeName == "int8")
			return new Int8(nodeDetails);
		else return nullptr;
	}

	static bool isClass()
	{

		//I may need to effectively prescan for all the different class names a solution may contain. 
		//That way my map of Classes, currently stored in the RootNode class can actually be reliably used.

	}
};

#endif
