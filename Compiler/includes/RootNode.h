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
	/**
	* Adds the specified pointer to the new Class object to the map of existing classes, as well as the name of the class in String form.
	* This is stored as a pair in the format <String, Class*>.
	* @param className The String representation of the identifier of the Class.
	* @param classPtr  The pointer to the new Class instance.
	*/
	void addClass(std::string className, Class* classPtr);
	
	/**
	* Getter method for the Class pointer specified by the identifier parameter.
	* @param className The string representation of the class to be found.
	* @return A pointer to an instance of a Class object. Can return a nullptr.
	*/
	Class* getClass(std::string className);
};

#endif