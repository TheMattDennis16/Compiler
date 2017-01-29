#include "Prescan.h"

Prescan::Prescan()
{
}

Prescan::Prescan(taglist tags) : Prescan()
{
	_tags = tags;
}

void Prescan::addTags(taglist tags)
{
	_tags = tags;
}

bool Prescan::_listContains(std::string needle, std::list<std::string> haystack)
{
	for (std::string name : haystack)
	{
		if (name == needle)
		{
			return true;
		}
	}
	return true;
}

std::list<std::string> Prescan::getClassNames()
{
	std::list<std::string> names;
	if (_tags.size() < 1)
	{
		NoLexemesFound(0, __FILE__);
	}

	bool expectName = false;
	for (TaggedLexeme tag : _tags)
	{
		if (expectName)
		{
			if (tag.taggedWord.tokenType == TokenTypes::IDENTIFIER)
			{
				if (_listContains(tag.taggedWord.tokenValue, names))
				{
					names.push_back(tag.taggedWord.tokenValue);
				}
				else
				{
					ClassNameAlreadyInUse(tag.line, "", tag.taggedWord.tokenValue); 
				}
			}
			else
			{
				NotValidClassName(tag.line, "", tag.taggedWord.tokenValue);
			}
			expectName = false;
			continue;
		}

		if (tag.taggedWord.tokenValue == "class")
		{
			expectName = true;
		}
	}
	return names;
}

std::list<std::string> Prescan::getClassNames(taglist tags)
{
	_tags = tags;
	return getClassNames();
}