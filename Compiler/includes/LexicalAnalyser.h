#ifndef LEXICAL_ANALYSER_HH
#define LEXICAL_ANALYSER_HH

#include "TokenCollection.h"
#include "DataTypes/Type.h"
#include "StringTagging.h"
#include "SymbolTable.h"
#include "TokenTypes.h"
#include "Error.h"
#include "Token.h"

#include <unordered_map>
#include <vector>
#include <iterator>
#include <utility>
#include <string>

class TaggedLexeme
{
public:
	Token taggedWord;
	int line;

	/**
	* Constructor for the TaggedLexeme class.
	* @param t A reference to the Token.
	* @param l An integer containing the Line of the source code the Token was found on.
	*/
	TaggedLexeme(const Token& t, const int l);
};

class LexicalAnalyser
{
private:
	TokenCollection _tokenCollection;
	StringTagging _taggerTools;
	std::vector<std::string> _lines;
	std::vector<TaggedLexeme> _output;
	std::vector<std::string>::iterator _linesIt;
	char _previousChar;
	char _nextChar = ' ';
	bool _isFinished = false;
	bool _toSkip = false;
	unsigned _iLine = 1;
	unsigned _iPosition = 0;

	/**
	* Advance the line position iterator of the source file. Reset the position of the character index on the new line.
	* @param hasHitEnd A reference to whether or not the iterator has reached the end of the file. This reference is modified.
	*/
	void _advanceLinePosition(bool& hasHitEnd);

	/**
	* Safe method for advancing the iterator across lines while updating the character indexing at the same time.
	* This has different functionality compared to _getNextChar();
	* @return True if successfully advanced the position and line
	*/
	bool _getNextCharNewLine();

	/**
	* Safe method for advancing character iterator positions on the same line, unsafe for traversing onto the next line.
	* @return True if successfully advanced the position
	*/
	bool _getNextChar();

	/**
	* Top level interface for advancing the stream position, more abstract then _getNextChar() and _getNextCharNewLine().
	* Depends on the _getNextChar() function to work.
	* @return True if successfully advanced the position
	*/
	bool getNextChar();

	/**
	* Adds the specified Token to the output std::vector. Wraps it as a TaggedLexeme by including the line number before addition.
	* @param token A reference to the specified Token class.
	*/
	void _addToOutput(const Token& token);

public:
	/**
	* Constructor for the LexicalAnalyser class.
	*/
	LexicalAnalyser();

	/**
	* Runs the tokenization process. Parses the specified std::vector parameter as lines of characters.
	* Characters are formed into groups based the syntax rules. A group of characters has the type identified
	* and then stored as a Token.
	* @param lines An std::vector where the subtype is a String. Each of these strings represents a line of the original source code.
	*/
	void tokenize(std::vector<std::string>& lines);

    /**
	* Returns the current output list of tagged Lexeme's as a pair with the String being the Token's representation.
	* @return An std::vector of <string, TaggedLexeme> pairs.
	*/
	std::vector<TaggedLexeme> getOutput();
};

#endif
