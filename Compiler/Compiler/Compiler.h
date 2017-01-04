#ifndef COMPILER_HH
#define COMPILER_HH

#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"
#include "CodeGenerator.h"
#include "FileHandling.h"

class Compiler
{
private:
	LexicalAnalyser _lex;
	SyntaxAnalyser _syn;
	CodeGenerator _gen;
	bool _toLLVM;

public:
	Compiler();
	Compiler(bool toLLVM);
	Compiler(std::string path);
	~Compiler();

	std::list<std::pair<std::string, TaggedLexeme>> getLexerOutput();
	void parseFile(std::string path);
	void toLLVMFlag(bool flag);
};

#endif