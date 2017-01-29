#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser()
{
	_linesIt = _lines.begin();
}

//Rather than append to a previous stored set of chars, forward iterate till a token or terminal symbol is identified
void LexicalAnalyser::tokenize(std::list<std::string>& list)
{
	//Set up ""globals"" for processing
	_lines = list;
	_linesIt = _lines.begin();
	_nextChar = (*_lines.begin()).at(0);
	bool isTokenised = false;
	while (!_isFinished)
	{	
		if(!_toSkip) getNextChar();
		if (_previousChar == '\n' || _previousChar == '\r')
		{
			if ((*_linesIt).size() == 0 && _linesIt != _lines.end())
			{
				_advanceLinePosition(isTokenised);
			}
			continue;
		}
		if (_previousChar == ' ' || _previousChar == '\t') 
			continue;

		//Operator symbol checking
		if (_previousChar == '&')
		{
			if (_nextChar == '&') { _addToOutput(Token(TokenTypes::OPERATOR, "&&")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::UNEXPECTED, "&"));
		}
		else if (_previousChar == '!')
		{
			if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "!=")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, "!")); 
		}
		else if (_previousChar == '/')
		{
			if (_nextChar == '/')
			{
				_advanceLinePosition(isTokenised);
				if (isTokenised) break;
				_getNextCharNewLine();
				continue;
			}
			else if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "/=")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, "/"));
		}
		else if (_previousChar == '\\')
		{
			 if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "\=")); getNextChar(); }
			else { _addToOutput(Token(TokenTypes::OPERATOR, "\\")); getNextChar(); }
		}
		else if (_previousChar == '*')
		{
			if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "*=")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, "*"));
		}
		else if (_previousChar == '+')
		{
			if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "+=")); getNextChar(); }
			else if (_nextChar == '+') { _addToOutput(Token(TokenTypes::OPERATOR, "++")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, "+"));
		}
		else if (_previousChar == '-')
		{
			if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "-=")); getNextChar(); }
			else if (_nextChar == '-') { _addToOutput(Token(TokenTypes::OPERATOR, "--")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, "-"));
		}
		else if (_previousChar == '=')
		{
			if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "==")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, "="));
		}
		else if (_previousChar == '>')
		{
			if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, ">=")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, ">"));
		}
		else if (_previousChar == '<')
		{
			if (_nextChar == '=') { _addToOutput(Token(TokenTypes::OPERATOR, "<=")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::OPERATOR, "<"));
		}
		else if (_previousChar == '|')
		{
			if (_nextChar == '|') { _addToOutput(Token(TokenTypes::OPERATOR, "||")); getNextChar(); }
			else _addToOutput(Token(TokenTypes::UNEXPECTED, "|"));
		}
		else if (_previousChar == '[')
			_addToOutput(Token(TokenTypes::OPERATOR, "["));
		else if (_previousChar == ']')
			_addToOutput(Token(TokenTypes::OPERATOR, "]"));
		else if (_previousChar == '(')
			_addToOutput(Token(TokenTypes::SYMBOL, "("));
		else if (_previousChar == ')')
			_addToOutput(Token(TokenTypes::SYMBOL, ")"));
		else if (_previousChar == '{')
			_addToOutput(Token(TokenTypes::SYMBOL, "{"));
		else if (_previousChar == '}')
			_addToOutput(Token(TokenTypes::SYMBOL, "}"));
		else if (_previousChar == ';')
			_addToOutput(Token(TokenTypes::SYMBOL, ";"));
		else if (_previousChar == ',')
			_addToOutput(Token(TokenTypes::SYMBOL, ","));

		//Not operator, must be: Identifier, Type, String Literal or a Number.
		if (_taggerTools.isChar(_previousChar) || _previousChar == '\"' || _previousChar == '\'' || _previousChar == '_')
		{
			bool isStringLiteralOpen = false;
			bool isCharOpen = false;
			bool isLocFinished = false;
			std::string word = "";

			if (_previousChar != '\"' && _previousChar != '\'')
				word += _previousChar;
			else if (_previousChar == '\"')
			{
				_addToOutput(Token(TokenTypes::SYMBOL, "\""));
				isStringLiteralOpen = true;
			}
			else 
			{
				_addToOutput(Token(TokenTypes::SYMBOL, "\'"));
				isCharOpen = true;
			}

			while (!isLocFinished)
			{
				//Parse out string literal open/closers.
				if (_nextChar == '\"')
				{
					if (!isCharOpen)
					{
						if (isStringLiteralOpen)
						{
							_addToOutput(Token(TokenTypes::VAR_VALUE, word));
							_addToOutput(Token(TokenTypes::SYMBOL, "\""));
							isLocFinished = true;
							getNextChar();
						}
					}
					else
					{
						word += '\"';
						getNextChar();
					}
				}
				else if (_nextChar == '\'')
				{
					if (!isStringLiteralOpen)
					{
						if (isCharOpen)
						{
							_addToOutput(Token(TokenTypes::VAR_VALUE, word));
							_addToOutput(Token(TokenTypes::SYMBOL, "\'"));
							isLocFinished = true;
							getNextChar();
						}
					}
					else
					{
						word += "'";
						getNextChar();
					}
				}
				else
				{
					//check if a string literal is open, if it is add literally everything to output until an end symbol is found.
					if (isStringLiteralOpen || isCharOpen)
					{
						word += _nextChar;
						getNextChar();
					}
					else
					{
						if (_tokenCollection.isStringBreakingChar(_nextChar))
						{
							StringTagging::removeWhitespace(word);
							Token search = _tokenCollection.isToken(word);
							Token charSearch = _tokenCollection.isToken(std::string("") + _nextChar);

							//Check to see if the word we've built is an actual type name, if not then it IS an identifier.
							if (search.tokenType == TokenTypes::TYPE)
							{
								_addToOutput(search);
							}
							else
							{
								_addToOutput(Token(TokenTypes::IDENTIFIER, word));
							}

							
							//Check to see if our _nextChar is actually a real token, if it isnt then its whitespace and who cares
							if (charSearch.tokenValue == ";")
							{
								_addToOutput(charSearch); getNextChar();
							}
							isLocFinished = true;
							//getNextChar();
							//TODO: Will have to keep an eye out for tokens not being matched.
						}
						else
						{
							word += _nextChar;
							getNextChar();
						}
					}
				}
			}
		}
		else if (_taggerTools.isNum(_previousChar))
		{
			//Include any '.'s found, for doubles etc.
			std::string number = "";
			while (_taggerTools.isNum(_previousChar) || _previousChar == '.')
			{
				number += _previousChar;
				if (_taggerTools.isNum(_nextChar) || _nextChar == '.')
					getNextChar();
				else break;
			}

			if (number.at(0) == '.')
				number = '0' + number.data();

			_addToOutput(Token(TokenTypes::VAR_VALUE, number));

			Token charSearch = _tokenCollection.isToken(std::string("") + _previousChar);
			if (charSearch.tokenValue == ";")
			{
				_addToOutput(charSearch);
			}
		}
	}
}

/*
	Take into account \n, as there's no guarentee an expression will finish on the same line as starting. E.G
	int a = 1
	+ 2;
*/
bool LexicalAnalyser::getNextChar()
{
	if (_toSkip) _toSkip = false;

	bool isFinishedNextLine = false;
	while (!isFinishedNextLine)
	{
		isFinishedNextLine = _getNextChar();
		if (_isFinished)
			return false;
	}
}

bool LexicalAnalyser::_getNextCharNewLine()
{
	if (_isFinished) return false;
	if (++_iPosition >= (*_linesIt).size())
	{
		bool hasHitEnd = false;
		_advanceLinePosition(hasHitEnd);

		if (hasHitEnd)
		{
			_previousChar = _nextChar;
			_isFinished = true;
			return true;
		}
	}
	if ((*_linesIt).size() <= 0)
		(*_linesIt) += '\n\n';
	_previousChar = (*_linesIt).at(0);
	_nextChar = (*_linesIt).at(1);
	_toSkip = true;
	return true;
}

bool LexicalAnalyser::_getNextChar()
{
	if (_isFinished) return false;
	if (++_iPosition >= (*_linesIt).size())
	{
		bool hasHitEnd = false;
		_advanceLinePosition(hasHitEnd);

		if (hasHitEnd)
		{
			_previousChar = _nextChar;
			_isFinished = true;
			return true;
		}
	}
	_previousChar = _nextChar;
	if ((*_linesIt).size() == 0)
		(*_linesIt) += '\n';
	_nextChar = (*_linesIt).at(_iPosition);
	return true;
}

void LexicalAnalyser::_advanceLinePosition(bool& hasHitEnd)
{
	if (++_linesIt == _lines.end())
		hasHitEnd = true;
	_iLine++;
	_iPosition = 0;
}

TaggedLexeme::TaggedLexeme(Token& t, int l)
{
	taggedWord = t;
	line = l;
}

void LexicalAnalyser::_addToOutput(Token& token)
{
	_output.push_back(TaggedLexeme(token, _iLine));
}

std::list<TaggedLexeme> LexicalAnalyser::getOutput()
{
	return _output;
}