#ifndef ROOT_NODE_HH
#define ROOT_NODE_HH

#include <string>
#include <unordered_map>

#include "ErrorCodes.h"
#include "Class.h"

class RootNode
{
private:
	std::unordered_map<std::string, Class*> _classes;

public:	
	void addClass(std::string className, Class* classPtr);
	Class* getClass(std::string className);
};

#endif