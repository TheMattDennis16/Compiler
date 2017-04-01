#ifndef INT_LITERAL_H
#define INT_LITERAL_H

#include "../Node.h"

class IntLiteral : public Node 
{
private:
	long long _intValue;
public:
	/**
	* Default constructor for the IntLiteral node. Sets a default value of 0.
	*/
	IntLiteral();

	/**
	* Overloaded constructor for the IntLiteral node. Sets the value equal to the provided parameter.
	* @param The value to set.
	*/
	IntLiteral::IntLiteral(long long value);
	
	/**
	* Sets the value of the integer.
	* @param value The value to assign to the inner variable.
	*/
	void setValue(long long value);

	/**
	* Gets the value of the literal.
	* @return The integer literal.
	*/
	long long getValue();
};

#endif