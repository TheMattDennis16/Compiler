#ifndef TYPE_HH
#define TYPE_HH

#include "Char.h"

#include <string>

class Type
{
public:
	int _id;
	int _size;
	std::string _typeName;
	std::string _value;
};

enum TypeID
{
	NEW_CHAR,
	NEW_INT,
	NEW_DOUBLE,
	NEW_BOOL,
	NEW_CLASS,
	NEW_VOID
};

#endif