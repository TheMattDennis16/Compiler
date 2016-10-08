#ifndef FILE_HANDLING_HH
#define FILE_HANDLING_HH

#include "Error.h"

#include <list>
#include <string>
#include <fstream>


class FileHandling
{
public:
	static std::list<std::string> getSource(std::string file);
};

#endif