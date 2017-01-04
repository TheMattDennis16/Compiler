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
	//Class level functions
	Function(
		std::list<FunctionParameter>& params, 
		std::string name,
		NodeDetails details
		);
	~Function();
	bool operator==(const Function& rhs);

	std::string getName();
	void addParameter(FunctionParameter& param);
	std::list<FunctionParameter> getParameters() const;
	void setBlock(Block* setBlock);
	Block* getBlock();
};

#endif