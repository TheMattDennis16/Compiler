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
	CHAR,
	INT,
	DOUBLE,
	BOOL
};

#endif