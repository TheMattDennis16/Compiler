#ifndef NODE_HH
#define NODE_HH

#include <string>
#include <memory>
#include <iostream>

#include "TokenTypes.h"
#include "NodeDetails.h"

class Node
{
public:
	class NodeDetails
	{
	private:
	public:
		Node* _parent;
		int _line;
		int _tokenType;

		/**
		* Constructor for the NodeDetails class, sets up the information needed for a base class node.
		* @param parentPtr A pointer to the parent Node of the current Node. Helps allow upwards navigation through the tree.
		* @param tokenType An integer identifying the type of token, accessed through the TokenTypes enumerator
		* @param line      The line of code the Node was originally found on.
		*/
		NodeDetails(Node* parentPtr, int tokenType, int line)
		{
			_parent = parentPtr;
			_line = line;
			_tokenType = tokenType;
		}
	};

	/**
	* Constructor for the Node class.
	* @param details The NodeDetails relevant to this Node.
	*/
	Node(NodeDetails details);

	virtual Node* getParent();

	/**
	* Sets the internal NodeDetails instance to the specified data. Requred due to restrictions with the Type system not having ownership in an AST yet
	* @param details The NodeDetails to be stored
	*/
	void setNodeDetails(NodeDetails details);

	/**
	* Basic deep comparison operator for the Node class. Should be overridden by inherited subclasses.
	*/
	bool operator==(const Node& right);

private:
	NodeDetails _details;
	virtual void stub(); //To remove?
};
#endif