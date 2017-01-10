#ifndef FUNCTION_HH
#define FUNCTION_HH

#include <string>
#include <list>

#include "DataTypes\Type.h"
#include "Block.h"
#include "Node.h"

class FunctionParameter
{
private:
public:
	Type* _type;
	std::string _name;

	/**
	* Constructor for the FunctionParameter class.
	* @param type A pointer to the base class pointer for the Type identification class.
	* @param name The string identifier representing the function parameter.
	*/
	FunctionParameter(Type* type, std::string name)
	{
		_type = type;
		_name = name;
	}
};

class FunctionParameterValue
{
private:
public:
	Type* _type;

	/**
	* The constructor for the FunctionParameterValue class. 
	* @param type Provides the type information for the value.
	*/
	FunctionParameterValue(Type* type)
	{
		_type = type;
	}
};

class Function : public Node
{
private:
	Block* _block;
	std::list<FunctionParameter> _params;
	std::string _name;

public:
	/**
	* Constructor for the Function node class. Represents a function as the components which it represents.
	* @param params   A reference to an std::list of type FunctionParameter. 
	*                 This therefore stores the FunctionParameter objects associated with this function signature.
	* @param name     The string representation of the identifier for this function signature.
	* @param details  Allows the Node details to be stored for extra information about this object.
	*/
	Function(
		std::list<FunctionParameter>& params, 
		std::string name,
		NodeDetails details
		);

	/**
	* Destructor for the Function class.
	*/
	~Function();

	/**
	* Operator overload for the comparison operator. Provides a deep comparison.
	* @param rhs The right hand side operand of the equality operator.
	* @return True if the two objects contain equal data.
	*/
	bool operator==(const Function& rhs);

	/**
	* Getter for the name identifier for this function.
	* @return the string representation of the name identifier.
	*/
	std::string getName();

	/**
	* Adds the reference to the specified parameter to the std::list of known parameters.
	* @param param The reference to the new FunctionParameter object to be stored.
	*/
	void addParameter(FunctionParameter& param);

	/**
	* Gets a copy of the std::list of stored parameters. Const qualified.
	* @return Returns the std::list of FunctionParameter objects.
	*/
	std::list<FunctionParameter> getParameters() const;

	/**
	* Setter for the Block element. This therefore sets the scope for the interior of the Function.
	* @param setBlock Sets the function's scope equal to the pointer to the new Block.
	*/
	void setBlock(Block* setBlock);

	/**
	* Getter for the Block scope for this Function signature.
	* @return The pointer to the Block scope.
	*/
	Block* getBlock();
};

#endif