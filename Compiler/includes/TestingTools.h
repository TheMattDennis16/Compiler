#include "LexicalAnalyser.h"
#include <string>
#include <list>
#include <chrono>

namespace TestingTools
{
	/**
	* Converts the std::list of TaggedLexemes into a string.
	*/
	std::string lexToString(std::vector<TaggedLexeme> list);

	/**
	* Gets the current time_point measured in microseconds.
	*/
	std::chrono::high_resolution_clock::time_point getCurrentTime();

	/**
	* Gets the difference between two time_points.
	*/
	long long getTimeDelta(
		std::chrono::high_resolution_clock::time_point t1,
		std::chrono::high_resolution_clock::time_point t2);
}
