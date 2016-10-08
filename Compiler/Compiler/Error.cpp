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