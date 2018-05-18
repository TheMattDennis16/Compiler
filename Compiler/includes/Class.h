#ifndef CLASS_HH
#define CLASS_HH

#include <string>
#include <vector>

#include "DataTypes/Type.h"
#include "FunctionCall.h"
#include "SymbolTable.h"
#include "ErrorCodes.h"
#include "Function.h"

class Class : public Type
{
private:
	std::string _name;
	std::vector<Function*> _functions;
	SymbolTable _symbolTable;

	/**
	* Find and return all Function objects which match the specified String.
	* @param name The String instance representing the name to be searched for in the std::vector of available Functions.
	* @return Returns a std::vector of pointers to Function objects.
	*/
	std::vector<Function*> _findAllFunctionNameMatches(std::string name);

public:
	/**
	* Constructor for the Class object. Stores the identifier of the class.
	* @param name The String instance containing the identifier of the class.
	*/
	Class(std::string name, Node::NodeDetails nodeDetails);

	/**
	* Destructor for the Class object. Performs any tear-down required.
	*/
	~Class();

	/**
	* Gets the identifier for the Class object.
	* @return The String containing the identifier for the class.
	*/
	std::string getName();

	/**
	* Sets the identifier for the Class object.
	* @param name Sets the private String identifier variable to the value specified.
	*/
	void setName(std::string name);

	/**
	* Checks whether or not the std::vector currently contains a matching Function signature. Shallow comparison comparing the pointer only.
	* @param function A pointer to the function signature to be checked against the std::vector
	* @return true if a match is found, false if one is not.
	*/
	bool containsFunctionSignature(Function* function);

	/**
	* Finds all function signatures in the current Class scope which match the specified fName String.
	* Iterates over these and does a check of all parameters to ensure the types match.
	* @param fName  The function name to find all parameter sets for.
	* @param params The value types entered which are used to compare against the expected values.
	* @return True if the funnction parameters match a result found by the function name specified.
	*/
	Function* doParamsMatchSignature(std::string fName, std::vector<FunctionParameterValue> params);


	/**
	* Method to call a specified function name with the parameters given.
	* @param fName  Function name to call.
	* @param params An std::vector list of FunctionParameterValue objects.
	* @return A FunctionCall object to be included in the tree.
	*/
	FunctionCall callFunction(std::string fName, std::vector<FunctionParameterValue> params);

	/**
	* Adds a pointer to a Function instance to the list of stored Functions.
	* @param function A pointer to the Function instance to add to the std::vector collection.
	*/
	void addFunction(Function* function);

	/**
	* Exposes the SymbolTable interface. Checks whether or not the Symbol specified is currently in the symbol table.
	* @param symbol A reference to the Symbol to check inside the symbol table. Performs a deep comparison of data.
	* @return True if the Symbol data specified is locatated inside the symbol table.
	*/
	bool isInSymbolTable(Symbol& symbol);

	/**
	* Exposes the SymbolTable interface. Adds the specified function parameter to the SymbolTable class.
	* DOES NOT CHECK FOR DUPLICATES BEFORE ADDITION.
	* @param symbol A reference to the Symbol to add.
	*/
	void addToSymbolTable(Symbol& symbol);
};

#endif
