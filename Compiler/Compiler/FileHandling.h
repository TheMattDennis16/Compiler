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
	static std::list<std::string> getSource(std::string file);
	static grammars getGrammars();
};

#endif