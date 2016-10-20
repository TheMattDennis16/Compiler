#ifndef STRING_TAGGING_HH
#define STRING_TAGGING_HH

#include <string>
#include <list>

// TODO: Rename to something that's actually correct
class StringTagging
{
public:
	bool isChar(char val);
	bool isNum(char val);
	bool isWhitespace(char val);

	static void removeWhitespace(std::string& toClean);
};

#endif