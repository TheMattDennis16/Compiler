#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

bool SymbolTable::containsSymbol(Symbol& symbol)
{
	return (std::find(_symbols.begin(), _symbols.end(), symbol) != _symbols.end());
}

void SymbolTable::addSymbol(Symbol& symbol)
{
	_symbols.push_back(symbol);
}