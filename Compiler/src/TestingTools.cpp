#include "TestingTools.h"
#include <iostream>
#include <chrono>
std::string TestingTools::lexToString(std::vector<TaggedLexeme> lines)
{
	std::string output = "";
	for (auto line : lines)
	{
		output += line.taggedWord.tokenValue + ",";
	}
	return output;
}

std::chrono::high_resolution_clock::time_point TestingTools::getCurrentTime()
{
	return std::chrono::high_resolution_clock::now();
}

long long TestingTools::getTimeDelta(
	std::chrono::high_resolution_clock::time_point t1,
	std::chrono::high_resolution_clock::time_point t2)
{
	return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}