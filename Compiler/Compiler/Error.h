#ifndef ERROR_HH
#define ERROR_HH
#define ERROR __LINE__, __FILE__

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
#endif