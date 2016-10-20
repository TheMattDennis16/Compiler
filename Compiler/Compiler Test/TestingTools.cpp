#include "TestingTools.h"

std::string TestingTools::lexToString(std::list<std::pair<std::string, TaggedLexeme>> lines)
{
	std::string output = "";
	for (auto line : lines)
	{
		output += line.first + ",";
	}
	return output;
}