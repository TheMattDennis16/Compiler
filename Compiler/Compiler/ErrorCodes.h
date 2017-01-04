#ifndef ERROR_CODES_HH
#define ERROR_CODES_HH

#include <string>

namespace ErrorCodes
{
	const std::string FUNCTION_NAME_DEFINED_IN_SCOPE = "Function name already defined in this scope.";
	const std::string CLASS_NAME_DEFINED_IN_SCOPE = "Class name already exists.";
	const std::string OBJECT_USE_NOT_VALID = "The usage of the specified word is invalid.";
	const std::string INVALID_CLASS_BRACES = "Missing opening brace on class definition.";
	const std::string IMBALANCED_BRACES_FOUND = "Imbalanced braces detected.";
	const std::string UNEXPECTED_SYMBOL_FOUND = "An unexpected symbol was found.";
	const std::string UNEXPECTED_TOKEN_FOUND = "An unexpected token was found.";
	const std::string IDENTIFIER_ALREADY_IN_USE_IN_SCOPE = "The specified identifier is already in use in this scope.";
};

#endif