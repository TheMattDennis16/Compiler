#ifndef SYMBOL_TABLE_HH
#define SYMBOL_TABLE_HH

#include "Symbol.h"
#include "DataTypes/Type.h"
#include "Block.h"

#include <algorithm>
#include <vector>
#include <string>

class SymbolTable
{
private:
	std::vector<Symbol> _symbols;

public:
	/**
	* Constructor for the SymbolTable class.
	*/
	SymbolTable();

	/**
	* Destructor for the SymbolTable class.
	*/
	~SymbolTable();

	/**
	* Checks whether or not the Symbol specified as a parameter is in the std::vector of Symbols. Performs pointer comparisons where necessary.
	* @param symbol A reference to the Symbol class instance to compare with the entries in the std::vector.
	* @return True if the Symbol is found, false if it is not.
	*/
	bool containsSymbol(Symbol& symbol);

	/**
	* Adds the specified symbol to the SymbolTable. Does not attempt to prevent duplicates.
	* @param symbol A reference to the Symbol instance to be added.
	*/
	void addSymbol(Symbol& symbol);
};

#endif
