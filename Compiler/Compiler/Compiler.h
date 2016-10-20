#ifndef COMPILER_HH
#define COMPILER_HH

#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"
#include "CodeGenerator.h"
#include "FileHandling.h"

class Compiler
{
private:
	LexicalAnalyser lex;
	SyntaxAnalyser syn;
	CodeGenerator gen;
	bool toLLVM;

	//std::list<std::pair<std::string, TaggedLexeme>> getLexerOutput();

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