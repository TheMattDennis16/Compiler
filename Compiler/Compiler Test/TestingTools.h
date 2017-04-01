#ifndef TESTING_TOOLS
#define TESTING_TOOLS

#include "../Compiler/LexicalAnalyser.h"
#include <string>
#include <list>

class TestingTools
{
private:
public:
	/**
	* Converts the std::list of TaggedLexemes into a string.
	*/
	static std::string lexToString(std::list<TaggedLexeme> list);
};

#endif