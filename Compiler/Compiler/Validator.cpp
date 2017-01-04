#include "Validator.h"

Validator::Validator(taglist tags)
{
	_nestingLevel = 0;
	_tokens = tags;
}

TaggedLexeme Validator::_getNext()
{
	if (++_it != _tokens.end())
	{
		return *_it;
	}
	return TaggedLexeme(Token(TokenTypes::UNEXPECTED, "Err"), 0);
}

// Function definition
// [TYPE/CLASS] [IDENTIFIER] ( [TYPE_IDENTIFIER_PAIRS] ) {
//
// Variable definition
// [TYPE/CLASS] [IDENTIFIER] ( [EXPR] ) ;
// or
// [TYPE/CLASS] [IDENTIFIER] ;
// or 
// [TYPE] [IDENTIFIER] [OP] [EXPR] ;
// Don't support operator overloading yet.
bool Validator::validateType() 
{
	TaggedLexeme current = (*_it);
	std::vector<TaggedLexeme> stack = { current };
	Class* isClass = nullptr;
	Type* isType = nullptr;
	// If neither a known type OR a user defined class throw error for unknown type.
	if (current.taggedWord.tokenType != TokenTypes::TYPE)
	{
		isClass = _rootNode.getClass(current.taggedWord.tokenValue);
		if (isClass == nullptr)
		{
			// Is neither type nor class. Throw error.
			UnexpectedToken(current.line, __FILE__, current.taggedWord.tokenValue);
		}
	}
	else
	{
		isType = TypeParsing::getType(current.taggedWord.tokenValue);
	}
	
	current = _getNext();
	stack.push_back(current);
	if (current.taggedWord.tokenType != TokenTypes::IDENTIFIER)
	{
		// Not an identifier - must be invalid name.
		NotValidWord(current.line, __FILE__, current.taggedWord.tokenValue);
	}

	//Check identifier isn't already in use.
	Type* toUse = nullptr;
	if (isType != nullptr)
	{
		toUse = isType;
		delete isClass;
	}
	else if (isClass != nullptr)
	{
		toUse = isClass;
		delete isType;
	}
	else
	{
		UnexpectedToken(current.line, __FILE__, current.taggedWord.tokenValue);
	}

	current = _getNext();
	stack.push_back(current);
	if (current.taggedWord.tokenType == TokenTypes::SYMBOL)
	{
		current = _getNext();

		// Must be one of top three cases
		if (current.taggedWord.tokenValue == "(")
		{
			if ((current = _getNext()).taggedWord.tokenValue == ")")
			{
				//No parameters.
				if ((current = _getNext()).taggedWord.tokenValue == ";")
				{
					// [TYPE/CLASS] [IDENTIFIER] ( [EXPR] ) ;
				}
				return true;
			}

			std::list<FunctionParameter> params = validateFunctionParameters();
			if (params.size() != 0)
			{
				for (FunctionParameter param : params)
					_activeFunction->addParameter(param);
			}
			else
			{
				//Must be second case: [TYPE/CLASS] [IDENTIFIER] ( [EXPR] ) ;
				validateExpression(")");
			}
			// Next part must be a ) symbol.

		}
		else if (current.taggedWord.tokenValue == ";")
		{
			Symbol newSymbol(stack.at(1).taggedWord.tokenValue, _activeBlock, toUse);
			// [TYPE/CLASS] [IDENTIFIER] ;
			if (!_activeClass->isInSymbolTable(newSymbol))
			{
				//Not found in symbol table.
				_activeClass->addToSymbolTable(newSymbol);
			}
			else
			{
				IdentifierAlreadyInUseInScope(current.line, __FILE__, current.taggedWord.tokenValue);
				//Already found in symbol table.
			}
		}
	}
	else if (current.taggedWord.tokenType == TokenTypes::OPERATOR)
	{
		//Node* newNode = new Assignment();
		//_activeBlock->addNode(newNode);
		// Must be Rule 4 (Assignment OP), next must evaluate to valid expression.
	}
	else
	{
		// Throw an error.
	}
}

//Function Parameters:
// TYPE IDENTIFIER
// TYPE IDENTIFIER , IDENTIFIER ...
std::list<FunctionParameter> Validator::validateFunctionParameters()
{
	TaggedLexeme current = (*_it);
}

// Iterate up through the tree to see if its nested in a loop
bool Validator::_isInLoop()
{
	Node* ptr = nullptr;
	bool isInLoop = false;
	while ((ptr = _activeBlock->getParent()) != nullptr)
	{
		if (For* f = dynamic_cast<For*>(ptr))
		{
			isInLoop = true;
			break;
		}
		else if (While* w = dynamic_cast<While*>(ptr))
		{
			isInLoop = true;
			break;
		}
	}
	return isInLoop;
}

// Statement Types
// IF ( [BOOL_EXPR] ) { 
// 
// WHILE ( [BOOL_EXPR] ) { 
// 
// FOR ( 
bool Validator::validateStatement()
{
	TaggedLexeme tag = (*_it);
	if (tag.taggedWord.tokenValue == "if")
	{
		_validateIf();
	}
	else if (tag.taggedWord.tokenValue == "for") 
	{
		// Only allow iterative controls.
		// Must follow syntax:
		// FOR ( EXPR; EXPR; EXPR) {
		// where the expressions must be null or (in order):
		// 1) type declaration/definition
		// 2) boolean checkable expression
		// 3) identifier iteration
	}
	else if (tag.taggedWord.tokenValue == "while") 
	{
	}
	else if (tag.taggedWord.tokenValue == "break")
	{
		if(_isInLoop())
			_activeBlock->addNode(new Break(NodeDetails(_activeFunction, tag.taggedWord.tokenType, tag.line)));
	}
	else if (tag.taggedWord.tokenValue == "continue")
	{
		if (_isInLoop())
			_activeBlock->addNode(new Continue(NodeDetails(_activeFunction, tag.taggedWord.tokenType, tag.line)));
	}
	else
	{
		//Unexpected
	}
}

// class [IDENTIFER] {
bool Validator::validateClass()
{
	auto tag = _getNext();
	if (_nestingLevel > 0)
		ImbalancedBraces(tag.line, __FILE__);

	_activeClass = new Class(tag.taggedWord.tokenValue);
	if (tag.taggedWord.tokenType != TokenTypes::IDENTIFIER)
		NotValidWord(tag.line, __FILE__, tag.taggedWord.tokenValue);
	tag = _getNext();

	if (tag.taggedWord.tokenType != TokenTypes::SYMBOL || tag.taggedWord.tokenValue != "{")
		InvalidClassBraces(tag.line, __FILE__);
	_nestingLevel++;
}

// Should always evaluate to:
// [IDENT] [OP] [VALUE]
// where [VALUE] can be another nested Expr.
// e.g.
// [IDENT] [OP] [IDENT] [OP] [IDENT] [OP] [VALUE] ;
// a        =      b     +      c     *    2      ;
// a        =   (  b     +   (  c     *    2    ));
// Except in case of function call. Which must be:
// IDENT ( FUNCTION_PARAMS_EXPR ) ;
Node* Validator::validateExpression(std::string endSymbol)
{
	TaggedLexeme current = (*_it);
	std::vector<TaggedLexeme> stack{ current, current = _getNext() };
	if (current.taggedWord.tokenValue == "(")
	{
		//must be function call.
		
		//if(_activeClass->containsFunctionSignature)
	}

	return nullptr;
}

bool Validator::validateSymbol()
{
	TaggedLexeme current = (*_it);
	if (current.taggedWord.tokenValue == "}")
	{
		if (_activeBlock != nullptr)
		{
			// _activeBlock needs to have the parent block assigned to it.
			// E.G
			// 
			// fn() {
			//   int a = 2 + 1;
			//   if(a == 3) {
			//     a = 4;
			//   }
			// }
			//
			// When you end the IF block you aren't moving to a nullptr
			// you're moving to its parent block, the one owned by the function.

			_activeBlock->isClosed = true;
			if (Function* f = dynamic_cast<Function*>(_activeBlock->getParent()))
			{
				_activeClass->addFunction(_activeFunction);
				_activeFunction = nullptr;
				_activeBlock = nullptr;
				--_nestingLevel;
				return true;
			}
			else
			{
				if (_activeBlock = dynamic_cast<Block*>(_activeBlock->getParent()))
				{
					--_nestingLevel;
				}
				else
				{
					//Throw unknown parent type error?
				}
			}
		}
		else if (--_nestingLevel == 0 && _activeClass != nullptr)
		{
			_rootNode.addClass(_activeClass->getName(), _activeClass);
			_activeClass = nullptr;
		}
		else if (_nestingLevel < 0)
		{
			ImbalancedBraces(current.line, __FILE__);
		}
	}
	//Should never occur section:
	else if (current.taggedWord.tokenValue == "{")
	{
		UnexpectedSymbol(current.line, __FILE__, '{');
		_nestingLevel++;
	}
}

bool Validator::validateSyntax()
{
	do 
	{
		TaggedLexeme current = (*_it);
		if (current.taggedWord.tokenValue == "class")
		{
			validateClass();
		}
		else if (current.taggedWord.tokenType == TokenTypes::KEYWORD)
		{
			//Statements & "CLASS" word
			validateStatement();
		}
		else if (current.taggedWord.tokenType == TokenTypes::TYPE)
		{
			validateType();
		}
		else if (current.taggedWord.tokenType == TokenTypes::IDENTIFIER)
		{
			Node* expression = validateExpression(";");
		}
		else if (current.taggedWord.tokenType == TokenTypes::SYMBOL)
		{
			validateSymbol();
		}
	} while (++_it != _tokens.end());
}

/*void Vaidator::advanceToToken(Token& token)
{
	while ((*_tokenIt).taggedWord == token)
	{
		if (_advanceIt())
		{
			auto token = *_tokenItNext;
			if (token.taggedWord.tokenValue != ";" || token.taggedWord.tokenValue != ";")
				break;
		}
	}
}*/