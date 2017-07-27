#ifndef STRING_TAGGING_HH
#define STRING_TAGGING_HH

#include <string>
#include <list>

// TODO: Rename to something that's actually correct
class StringTagging
{
private:
public:
	/**
	* Checks whether the value specified is a valid character in the range ([a-z], [A-Z]).
	* @param val The character value to be checked.
	* @return True if the character specified falls within the valid ranges.
	*/
	bool isChar(char val);

	/**
	* Checks whether the character specified is a valid integer number between the ranges of [0-9].
	* @param val The character value to be checked
	* @return True if the character specified falls within the valid ranges.
	*/
	bool isNum(char val);
	
	/**
	* Checks whether the character specified is a valid whitespace character (' ', '\t').
	* @param val The character value to be checked
	* @return True if the character specified falls within the valid ranges.
	*/
	bool isWhitespace(char val);

	/**
	* Removes any whitespace characters from a string.
	* @param toClean A reference to the String to be checked.
	*/
	static void removeWhitespace(std::string& toClean);
};

#endif