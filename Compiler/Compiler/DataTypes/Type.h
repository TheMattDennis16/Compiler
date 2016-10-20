#ifndef TYPE_HH
#define TYPE_HH

#include <string>

class Type
{
public:
	int id;
	int size;
	std::string typeName;
};

enum TypeID
{
	NEW_CHAR,
	NEW_INT,
	NEW_DOUBLE,
	NEW_BOOL
};

#endif