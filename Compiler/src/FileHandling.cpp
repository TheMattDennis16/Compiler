#include "FileHandling.h"

std::vector<std::string> FileHandling::getSource(std::string file)
{
	std::ifstream fileAccessor;
	std::vector<std::string> fileContents;

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
		FileNotFound(__LINE__, __FILE__);
	}
	return fileContents;
}