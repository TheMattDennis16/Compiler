#include "TestingTools.h"

std::string TestingTools::lexToString(std::list<TaggedLexeme> lines)
{
	std::string output = "";
	for (auto line : lines)
	{
		output += line.taggedWord.tokenValue + ",";
	}
	return output;
}