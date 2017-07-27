#include "Compiler.h"

Compiler::Compiler()
{
	_toLLVM = false;
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
	_lex.tokenize(lines);
	auto output = getLexerOutput();
	_pre.addTags(output);
	std::vector<std::string> classNames = _pre.getClassNames();

}

std::vector<TaggedLexeme> Compiler::getLexerOutput()
{
	return _lex.getOutput();
}

void Compiler::toLLVMFlag(bool flag)
{
	_toLLVM = flag;
}