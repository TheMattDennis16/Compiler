#include "Compiler.h"

#include <iostream>
#include <string>

void showHelp()
{
    std::cout << "Compiler correct usage:" << std::endl;
    std::cout << "./compiler filename" << std::endl;
    std::cout << "\n" << std::endl;
	std::cout << "To compile a program simply reference the specified file" << std::endl;
	std::cout << "To switch target from ASM output to LLVM ASM use --to-llvm after file reference" << std::endl;
	std::cout << "The final parameter should be the file to compile" << std::endl;
    std::cout << "\n" << std::endl;
}

bool contains(int argc, char* argv[], std::string value)
{
    bool returnValue { false };
    for (size_t i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == value)
        {
            returnValue = true;
            break;
        }
    }
    return returnValue;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
    {
        std::cout << "No input parameters found!" << std::endl;
        return 1;
    }

	if (contains(argc, argv, "-h") || contains(argc, argv, "--help"))
        showHelp();
	else
	{
		Compiler compiler;
		if (argc > 2)
		{
			if (contains(argc, argv, "--to-llvm"))
				compiler.toLLVMFlag(true);
			compiler.parseFile(argv[1]);
		}
		else compiler.parseFile(argv[1]);
	}
}
