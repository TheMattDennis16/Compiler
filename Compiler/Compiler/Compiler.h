#ifndef COMPILER_HH
#define COMPILER_HH

#include "LexicalAnalyser.h"
#include "CodeGenerator.h"
#include "FileHandling.h"

class Compiler
{
private:
	LexicalAnalyser _lex;
	CodeGenerator _gen;
	bool _toLLVM;

public:
	/**
	* Default constructor for the Compiler class.
	*/
	Compiler();

	/**
	* Constructor for the Compiler class. toLLVM parameter specifies whether or not to target the LLVM backend when generating code.
	* @param toLLVM Boolean to specify whether or not to target the LLVM backend.
	*/
	Compiler(bool toLLVM);

	/**
	* Constructor for the Compiler class. path parameter specifies the path to the source code file to be compiled.
	* Automatically calls the parse function and parses the file.
	* @param path A string instance of the path to the source code file to compile.
	*/
	Compiler(std::string path);

	/**
	* Destructor for the Compiler class.
	*/
	~Compiler();

	/**
	* Returns the output of the Lexical Analyser. 
	* @return An std::list of pairs. Each pair consists of a String and a TaggedLexeme.
	*/
	std::list<std::pair<std::string, TaggedLexeme>> getLexerOutput();

	/**
	* Parses the file specified in the parameter String.
	* @param path The path to the file to parse.
	*/
	void parseFile(std::string path);

	/**
	* Sets the flag required to target the LLVM backend.
	* @param flag Sets the state of the boolean variable.
	*/
	void toLLVMFlag(bool flag);
};

#endif