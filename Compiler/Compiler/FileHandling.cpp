#include "FileHandling.h"

std::list<std::string> FileHandling::getSource(std::string file)
{
	std::ifstream fileAccessor;
	std::list<std::string> fileContents;

	fileAccessor.open(file);
	if (fileAccessor.is_open())
	{
		std::string line;
		while (!fileAccessor.eof())
		{
			getline(fileAccessor, line);
			fileContents.push_back(line);
		}
		fileAccessor.close();
	}
	else
	{
		FileNotFound(ERROR);
	}
	return fileContents;
}