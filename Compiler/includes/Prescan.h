#ifndef PRESCAN_HH
#define PRESCAN_HH

#include <vector>
#include <string>

#include "LexicalAnalyser.h"

typedef std::vector<TaggedLexeme> taglist;

class Prescan
{
private:
	taglist _tags;
	bool _listContains(std::string needle, std::vector<std::string> haystack);

public:
	/**
	*
	*/
	Prescan();
	
	/**
	*
	*/
	Prescan(taglist tags);

	void addTags(taglist tags);

	std::vector<std::string> getClassNames();

	std::vector<std::string> getClassNames(taglist tags);
};

#endif