#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser()
{
	linesIt = lines.begin();
}

//Rather than append to a previous stored set of chars, forward iterate till a token or terminal symbol is identified
void LexicalAnalyser::tokenize(std::list<std::string>& list)
{
	//Set up ""globals"" for processing
	lines = list;
	linesIt = lines.begin();
	nextChar = (*lines.begin()).at(0);
	bool isTokenised = false;

	while (true)
	{	
		if (!getNextChar())
		{
			break;
		}
		if (nextChar == '\n' || nextChar == '\r')
			_advanceLinePosition(isTokenised);

		//Operator symbol checking
		if (previousChar == '&')
		{
			if (nextChar == '&') { addToOutput(Token(TokenTypes::OPERATOR, "&&")); }
			else addToOutput(Token(TokenTypes::UNEXPECTED, "&"));
		}
		else if (previousChar == '!')
		{
			if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, "!=")); }
			else addToOutput(Token(TokenTypes::OPERATOR, "!")); 
		}
		else if (previousChar == '\\')
		{
			if (nextChar == '\\') { _advanceLinePosition(isTokenised); }
			else if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, "\=")); }
			else addToOutput(Token(TokenTypes::OPERATOR, "\\"));
		}
		else if (previousChar == '*')
		{
			if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, "*="));  }
			else addToOutput(Token(TokenTypes::OPERATOR, "*"));
		}
		else if (previousChar == '+')
		{
			if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, "+="));  }
			else addToOutput(Token(TokenTypes::OPERATOR, "+"));
		}
		else if (previousChar == '-')
		{
			if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, "-=")); }
			else addToOutput(Token(TokenTypes::OPERATOR, "-"));
		}
		else if (previousChar == '=')
		{
			if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, "==")); }
			else addToOutput(Token(TokenTypes::OPERATOR, "="));
		}
		else if (previousChar == '>')
		{
			if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, ">=")); }
			else addToOutput(Token(TokenTypes::OPERATOR, ">"));
		}
		else if (previousChar == '<')
		{
			if (nextChar == '=') { addToOutput(Token(TokenTypes::OPERATOR, "<=")); }
			else addToOutput(Token(TokenTypes::OPERATOR, "<"));
		}
		else if (previousChar == '|')
		{
			if (nextChar == '|') { addToOutput(Token(TokenTypes::OPERATOR, "||")); }
			else addToOutput(Token(TokenTypes::UNEXPECTED, "|"));
		}
		else if (nextChar == '[')
			addToOutput(Token(TokenTypes::OPERATOR, "["));
		else if (nextChar == ']')
			addToOutput(Token(TokenTypes::OPERATOR, "]"));
		else if (nextChar == '(')
			addToOutput(Token(TokenTypes::SYMBOL, "("));
		else if (nextChar == ')')
			addToOutput(Token(TokenTypes::SYMBOL, ")"));
		else if (nextChar == '{')
			addToOutput(Token(TokenTypes::SYMBOL, "{"));
		else if (nextChar == '}')
			addToOutput(Token(TokenTypes::SYMBOL, "}"));
		else if (nextChar == ';')
			addToOutput(Token(TokenTypes::SYMBOL, ";"));

		//Not operator, must be: Identifier, Type, String Literal or a Number.
		if (taggerTools.isChar(nextChar))
		{
			std::string word = std::string(std::string("") + previousChar);
			bool isStringLiteralOpen = false;
			bool isCharOpen = false;
			bool isFinished = false;

			while (!isFinished)
			{
				//Parse out string literal open/closers.
				if (nextChar == '"')
				{
					if (isStringLiteralOpen)
					{
						addToOutput(Token(TokenTypes::VAR_VALUE, word));
						addToOutput(Token(TokenTypes::SYMBOL, "\""));
						isFinished = true;
					}
					else
					{
						addToOutput(Token(TokenTypes::SYMBOL, "\""));
					}
				}
				else if (nextChar == '\'')
				{
					if (isCharOpen)
					{
						addToOutput(Token(TokenTypes::VAR_VALUE, word));
						addToOutput(Token(TokenTypes::SYMBOL, "\'"));
						isFinished = true;
					}
					else if (!isCharOpen)
					{
						addToOutput(Token(TokenTypes::SYMBOL, "\'"));
					}
				}
				else
				{
					//check if a string literal is open, if it is add literally everything to output
					if (isStringLiteralOpen || isCharOpen)
					{
						word += nextChar;
						getNextChar();
					}
					else
					{
						if (tokenCollection.isStringBreakingChar(nextChar))
						{
							Token search = tokenCollection.isToken(word);
							Token charSearch = tokenCollection.isToken(std::string("") + nextChar);

							//Check to see if the word we've built is an actual type name, if not then it IS an identifier.
							if (search.tokenType == TokenTypes::TYPE)
							{
								addToOutput(search);
							}
							else
							{
								addToOutput(Token(TokenTypes::IDENTIFIER, word));
							}

							//Check to see if our nextChar is actually a real token, if it isnt then its whitespace and who cares
							if (charSearch.tokenType != TokenTypes::NOT_TOKEN)
							{
								addToOutput(charSearch);
							}
							isFinished = true;
							//TODO: Will have to keep an eye out for tokens not being matched.
						}
						else
						{
							word += nextChar;
							getNextChar();
						}
					}
				}
			}
		}
		else if (taggerTools.isNum(nextChar))
		{
			//Include any '.'s found, for doubles etc.
			std::string number = "";
			while (taggerTools.isNum(nextChar) || nextChar == '.')
			{
				number += nextChar;
				getNextChar();
			}
			addToOutput(Token(TokenTypes::VAR_VALUE, number));

			Token charSearch = tokenCollection.isToken(std::string("") + nextChar);
			if (charSearch.tokenType != TokenTypes::NOT_TOKEN)
			{
				addToOutput(charSearch);
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
	//Update to new position if needed.
	bool isFinishedNextLine = false;
	while (!isFinishedNextLine)
	{
		isFinishedNextLine = _getNextChar();
		if (isFinished)
			return false;
	}
}

bool LexicalAnalyser::_getNextChar()
{
	if (++iPosition >= (*linesIt).size())
	{
		bool hasHitEnd = false;
		_advanceLinePosition(hasHitEnd);
		
		if (hasHitEnd)
		{
			isFinished = true;
			return true;
		}
	}
	previousChar = nextChar;
	nextChar = (*linesIt).at(iPosition);
	return true;
}

void LexicalAnalyser::_advanceLinePosition(bool& hasHitEnd)
{
	if (++linesIt == lines.end())
		hasHitEnd = true;
	iLine++;
	iPosition = 0;
}

TaggedLexeme::TaggedLexeme(Token& t, int l)
{
	taggedWord = t;
	line = l;
}

void LexicalAnalyser::addToOutput(Token& token)
{
	output.push_back(std::pair<std::string, TaggedLexeme>(token.tokenValue, TaggedLexeme(token, iLine)));
}

std::list<std::pair<std::string, TaggedLexeme>> LexicalAnalyser::getOutput()
{
	return output;
}