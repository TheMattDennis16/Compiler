#include "FileHandling.h"

grammars FileHandling::getGrammars()
{
	grammars output;
	std::vector<std::string> singleGrammar;
	auto gramLines = getSource("grammars.txt");
	for (std::string grammar : gramLines)
	{
		std::string word = "";
		for (char letter : grammar)
		{
			if (letter == ' ' || letter == '\n')
			{
				singleGrammar.push_back(word);
			}
			else
			{
				word += letter;
			}
		}
	}
	return output;
}

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