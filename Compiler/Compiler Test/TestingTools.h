#ifndef TESTING_TOOLS
#define TESTING_TOOLS

#include "../Compiler/LexicalAnalyser.h"
#include <string>
#include <list>

class TestingTools
{
private:
public:
	static std::string lexToString(std::list<std::pair<std::string, TaggedLexeme>>);
};

#endif