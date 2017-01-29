#ifndef PRESCAN_HH
#define PRESCAN_HH

#include <list>
#include <string>

#include "LexicalAnalyser.h"

typedef std::list<TaggedLexeme> taglist;

class Prescan
{
private:
	taglist _tags;
	bool _listContains(std::string needle, std::list<std::string> haystack);

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

	std::list<std::string> getClassNames();

	std::list<std::string> getClassNames(taglist tags);
};

#endif