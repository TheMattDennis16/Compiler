#include "Compiler.h"

Compiler::Compiler()
{
	toLLVM = false;
}

Compiler::Compiler(bool toLLVM) : Compiler()
{
	toLLVM = toLLVM;
}

Compiler::Compiler(std::string path) : Compiler()
{
	parseFile(path);
}

Compiler::~Compiler()
{
}

void Compiler::parseFile(std::string path)
{
	auto lines = FileHandling::getSource(path);
	lex.tokenize(lines);

}

void Compiler::toLLVMFlag(bool flag)
{
	toLLVM = flag;
}