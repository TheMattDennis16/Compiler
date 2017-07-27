#ifndef ERROR_CODES_HH
#define ERROR_CODES_HH

#include <string>

namespace ErrorCodes
{
	//Naming Errors
	const std::string IDENTIFIER_ALREADY_IN_USE_IN_SCOPE = "The specified identifier is already in use in this scope.";
	const std::string FUNCTION_NAME_DEFINED_IN_SCOPE = "Function name already defined in this scope.";
	const std::string CLASS_NAME_DEFINED_IN_SCOPE = "Class name already exists.";
	const std::string NOT_VALID_CLASS_NAME = "This name is not a valid class name.";

	//Unexpected Lexeme Errors
	const std::string UNEXPECTED_SYMBOL_FOUND = "An unexpected symbol was found.";
	const std::string UNEXPECTED_TOKEN_FOUND = "An unexpected token was found.";

	//Brace usage
	const std::string INVALID_CLASS_BRACES = "Missing opening brace on class definition.";
	const std::string IMBALANCED_BRACES_FOUND = "Imbalanced braces detected.";

	//Unknown node type
	const std::string INVALID_PARENT_NODE_TYPE = "Could not cast to the known parent type.";

	//Loop Based Errors
	const std::string CANNOT_BREAK_NOT_IN_LOOP = "Cannot use break when not in either a for or while loop.";
	const std::string CANNOT_CONTINUE_NOT_IN_LOOP = "Cannot use continue when not in either a for or while loop";

	//Other
	const std::string OBJECT_USE_NOT_VALID = "The usage of the specified word is invalid.";
	const std::string NO_LEXEMES_FOUND = "No lexemes were found for parsing into the AST.";
};

#endif