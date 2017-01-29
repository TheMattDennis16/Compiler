#ifndef ERROR_HH
#define ERROR_HH
#define ERROR __LINE__, __FILE__

#include "ErrorCodes.h"

#include <iostream>
#include <cstdlib>
#include <string>

class ErrorHandling
{
private:
public:
	virtual void Throw(std::string msg);
};
class Fatal : public ErrorHandling
{
private:
public:
	void Throw(std::string msg);
};

class Warning : public ErrorHandling
{
private:
public:
	void Throw(std::string msg);
};

class FileNotFound : Fatal
{
private:
public:
	FileNotFound(const int line, const char* file);
};

class OutOfBounds : Fatal
{
private:
public:
	OutOfBounds(const int line, const char* file);
};

class NotValidWord : Fatal
{
private:
public:
	NotValidWord(const int line, const char* file, std::string word);
};

class InvalidClassBraces : Fatal
{
private:
public:
	InvalidClassBraces(const int line, const char* file);
};

class ImbalancedBraces : Fatal
{
private:
public:
	ImbalancedBraces(const int line, const char* file);
};

class UnexpectedSymbol : Warning
{
private:
public:
	UnexpectedSymbol(const int line, const char* file, char symbol);
};

class UnexpectedToken : Fatal
{
private:
public:
	UnexpectedToken(const int line, const char* file, std::string token);
};

class IdentifierAlreadyInUseInScope : Fatal
{
private:
public:
	IdentifierAlreadyInUseInScope(const int line, const char* file, std::string identifier);
};

class ClassNameAlreadyInUse : Warning
{
private:
public:
	ClassNameAlreadyInUse(const int line, const char* file, std::string identifier);
};

class NoLexemesFound : Fatal
{
private:
public:
	NoLexemesFound(const int line, const char* file);
};

class NotExpectedParentPointerType : Warning
{
private:
public:
	NotExpectedParentPointerType(const int line, const char* file, std::string expected);
};

class BreakNotInLoop : Warning
{
private:
public:
	BreakNotInLoop(const int line, const char* file);
};

class ContinueNotInLoop : Warning
{
private:
public:
	ContinueNotInLoop(const int line, const char* file);
};

class NotValidClassName : Warning
{
private:
public:
	NotValidClassName(const int line, const char* file, std::string identifier);
};
#endif