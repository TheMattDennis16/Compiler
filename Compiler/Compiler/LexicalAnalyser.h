#ifndef LEXICAL_ANALYSER_HH
#define LEXICAL_ANALYSER_HH

#include "TokenCollection.h"
#include "DataTypes\Type.h"
#include "StringTagging.h"
#include "SymbolTable.h"
#include "TokenTypes.h"
#include "Error.h"
#include "Token.h"

#include <unordered_map>
#include <iterator>
#include <utility>
#include <string>
#include <list>

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
	TokenCollection _tokenCollection;
	StringTagging _taggerTools;
	std::list<std::string> _lines;
	std::list<std::pair<std::string, TaggedLexeme>> _output;
	std::list<std::string>::iterator _linesIt;
	char _previousChar;
	char _nextChar = ' ';
	bool _isFinished = false;
	bool _toSkip = false;
	int _iLine = 1;
	int _iPosition = 0;

	void _advanceLinePosition(bool& hasHitEnd);
	bool _getNextCharNewLine();
	bool _getNextChar();
	bool getNextChar();
	void _addToOutput(Token& token);

public:
	LexicalAnalyser();
	void tokenize(std::list<std::string>& lines);
	std::list<std::pair<std::string, TaggedLexeme>> getOutput();
};

#endif