#include "RootNode.h"

void RootNode::addClass(std::string className, Class* classPtr)
{
	if (getClass(className) == nullptr)
	{
		std::cerr << ErrorCodes::CLASS_NAME_DEFINED_IN_SCOPE << std::endl;
	}
	else _classes.insert(std::pair<std::string, Class*>(classPtr->getName(), classPtr));
}

Class* RootNode::getClass(std::string className)
{
	if (_classes.find(className) == _classes.end())
		return nullptr;
	return _classes.at(className);
}