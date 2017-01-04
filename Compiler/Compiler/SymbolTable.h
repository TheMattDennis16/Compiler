#ifndef SYMBOL_TABLE_HH
#define SYMBOL_TABLE_HH

#include "Symbol.h"
#include "DataTypes\Type.h"
#include "Block.h"

#include <list>
#include <string>

class SymbolTable
{
private:
	std::list<Symbol> _symbols;

public:
	SymbolTable();
	~SymbolTable();
	bool containsSymbol(Symbol& symbol);
	void addSymbol(Symbol& symbol);
};

#endif