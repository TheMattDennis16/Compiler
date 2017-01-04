#include "Error.h"

void ErrorHandling::Throw(std::string msg)
{ }

void Warning::Throw(std::string msg)
{
	std::cout << msg << std::endl;
}

void Fatal::Throw(std::string msg)
{
	std::cerr << msg << std::endl;
	std::cerr << "Terminating Program" << std::endl;
	std::exit(1);
}

FileNotFound::FileNotFound(const int line, const char* file)
{
	Throw("File Not Found at Line " + std::to_string(line) + " in File " + file);
}

OutOfBounds::OutOfBounds(const int line, const char* file)
{
	Throw("Out of bounds at Line " + std::to_string(line) + " in File " + file);
}

NotValidWord::NotValidWord(const int line, const char* file, std::string word)
{
	Throw(ErrorCodes::OBJECT_USE_NOT_VALID + " " + std::to_string(line) + " in File " + file + " with keyword: " + word);
}

InvalidClassBraces::InvalidClassBraces(const int line, const char* file)
{
	Throw(ErrorCodes::INVALID_CLASS_BRACES + " " + std::to_string(line) + " in File " + file);
}

ImbalancedBraces::ImbalancedBraces(const int line, const char* file)
{
	Throw(ErrorCodes::IMBALANCED_BRACES_FOUND + " " + std::to_string(line) + " in File " + file);
}

UnexpectedSymbol::UnexpectedSymbol(const int line, const char* file, char symbol)
{
	Throw(ErrorCodes::UNEXPECTED_SYMBOL_FOUND + " " + std::to_string(line) + " in File " + file + " with symbol: " + symbol);
}

UnexpectedToken::UnexpectedToken(const int line, const char* file, std::string token)
{
	Throw(ErrorCodes::UNEXPECTED_TOKEN_FOUND + " " + std::to_string(line) + "in File " + file + " with Token: " + token);
}

IdentifierAlreadyInUseInScope::IdentifierAlreadyInUseInScope(const int line, const char* file, std::string identifier)
{
	Throw(ErrorCodes::IDENTIFIER_ALREADY_IN_USE_IN_SCOPE + " " + std::to_string(line) + "in File " + file + " with Identifier: " + identifier);
}