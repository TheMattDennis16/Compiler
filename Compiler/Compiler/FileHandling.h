#ifndef FILE_HANDLING_HH
#define FILE_HANDLING_HH

#include "Error.h"

#include <list>
#include <vector>
#include <string>
#include <fstream>

typedef std::vector<std::vector<std::string>> grammars;

class FileHandling
{
public:
	/**
	* Static method to get the source code from a file. Uses the file parameter to access it from the file-system.
	* Splits the source code into individual lines. Adds each line to an std::list ready for returning.
	* @param file The path to the file to parse.
	* @return An std::list of String's containing each line in the source code file. 
	          Returns an empty set if an error occurred, however an Error is generated and logged.
	*/
	static std::list<std::string> getSource(std::string file);
};

#endif