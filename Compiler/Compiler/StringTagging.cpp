#include "StringTagging.h"

bool StringTagging::isChar(char val)
{
	if (val >= 65 && val <= 90 || val >= 97 && val <= 122) return true;
	else return false;
}

bool StringTagging::isNum(char val)
{
	if (val >= 48 && val <= 57) return true;
	else return false;
}

bool StringTagging::isWhitespace(char val)
{
	if (val == ' ' || val == '\t') return true;
	else return false;
}