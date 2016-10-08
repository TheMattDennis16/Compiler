
#include "Compiler.h"

#include <iostream>
#include <string>

void showHelp()
{
	std::cout << "To compile a program simply reference the specified file" << std::endl;
	std::cout << "To switch target from ASM output to LLVM ASM use --switch after file reference" << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { printf("No input parameters found!"); return 1; }

	if (argv[1] == "--help")
		showHelp();
	else
	{
		Compiler compiler;
		if (argc > 2)
		{
			if (argv[2] == "--switch")
				compiler.toLLVMFlag(true);
			compiler.parseFile(argv[1]);
		}
		else compiler.parseFile(argv[1]);
	}
}