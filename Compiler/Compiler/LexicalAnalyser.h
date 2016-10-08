#ifndef LEXICAL_ANALYSER_HH
#define LEXICAL_ANALYSER_HH

#include "DataTypes\Type.h"
#include "TokenCollection.h"
#include "TokenTypes.h"
#include "Token.h"
#include "StringTagging.h"
#include "Error.h"

#include <utility>
#include <list>
#include <unordered_map>
#include <string>
#include <iterator>

class TaggedLexeme
{
public:
	Token taggedWord;
	int line;
	TaggedLexeme(Token& t, int l);
};

class LexicalAnalyser
{
private:
	TokenCollection tokenCollection;
	StringTagging taggerTools;
	std::list<std::string> lines;
	std::list<std::pair<std::string, TaggedLexeme>> output;
	std::list<std::string>::iterator linesIt;
	char previousChar;
	char nextChar = ' ';
	bool isFinished = false;
	int iLine = 1;
	int iPosition = 0;

	void _advanceLinePosition(bool& hasHitEnd);
	bool _getNextChar();
	bool getNextChar();
	void addToOutput(Token& token);

public:
	LexicalAnalyser();
	void tokenize(std::list<std::string>& lines);
	std::list<std::pair<std::string, TaggedLexeme>> getOutput();
};

#endif