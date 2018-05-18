#include "Validator.h"

Validator::Validator()
{
	_nestingLevel = 0;
}

Validator::Validator(taglist tags) : Validator()
{
	_tokens = tags;
    _it = _tokens.begin();
}

TaggedLexeme Validator::_getNext()
{
	if (++_it != _tokens.end())
	{
		return *_it;
	}
	return TaggedLexeme(Token(TokenTypes::UNEXPECTED, "Err"), 0);
}

Node* Validator::_validateOperator(std::vector<TaggedLexeme> stack)
{
	// Called by the _validateExpr function
	// [IDENTIFIER] [OP] [EXPR] ;
	return nullptr;
}

Node* Validator::_validateType()
{
	// Function definition
	// [TYPE/CLASS] [IDENTIFIER] ( [TYPE_IDENTIFIER_PAIRS] ) {
	//
	// Object definition with implied call to a Constructor function.
	// [CLASS] [IDENTIFIER] ( [EXPR] ) ;
	// or
	// [TYPE/CLASS] [IDENTIFIER] ;
	// or (in which case go to _validateAssignment with current stack).
	// [TYPE] [IDENTIFIER] [OP] [EXPR] ;
	// Don't support operator overloading yet.

	TaggedLexeme current = (*_it);
	std::vector<TaggedLexeme> stack = { current };
	Class* isClass = nullptr;
	Type* isType = nullptr;
	// If it isn't a TYPE then it's a class. We may not know the exact class yet. Verify later.
    if (current.taggedWord.tokenType != TokenTypes::TYPE)
	{
		isClass = new Class(current.taggedWord.tokenValue,
            Node::NodeDetails(nullptr, current.taggedWord.tokenType, current.line));
	}
	else
	{
		isType = TypeParsing::getType(current.taggedWord.tokenValue, Node::NodeDetails(nullptr,0,0));
	}


	current = _getNext();
	stack.push_back(current);
	if (current.taggedWord.tokenType != TokenTypes::IDENTIFIER)
	{
		// Not an identifier - must be invalid name.
		NotValidWord(current.line, __FILE__, current.taggedWord.tokenValue);
	}
    std::string identifier = current.taggedWord.tokenValue;

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

    printf("printing\n");
    printf(current.taggedWord.tokenValue.c_str());
	current = _getNext();
	stack.push_back(current);
    printf(current.taggedWord.tokenValue.c_str());
	if (current.taggedWord.tokenType == TokenTypes::SYMBOL)
	{
        printf("is symbol\n");
		current = _getNext();
	    stack.push_back(current);


		// Must be one of top three cases
		if (current.taggedWord.tokenValue == "(")
		{
			//Top two cases
			if ((current = _getNext()).taggedWord.tokenValue == ")")
			{
				//No parameters.
				if ((current = _getNext()).taggedWord.tokenValue == ";")
				{
					// [CLASS] [IDENTIFIER] ( [EXPR] ) ; with no EXPR paramaters.

					return new Node(Node::NodeDetails(nullptr, 0, 0));
				}
				else
				{
					UnexpectedToken(current.line, __FILE__, current.taggedWord.tokenValue);
					return nullptr;
				}
			}

			std::vector<FunctionParameter> params = _validateFunctionParameters();
			if (params.size() != 0)
			{
				for (FunctionParameter param : params)
					_activeFunction->addParameter(param);
			}
			else
			{
				//Must be second case: [TYPE/CLASS] [IDENTIFIER] ( [EXPR] ) ;
				Node* expr = _validateExpression();
				current = _getNext();
				if (current.taggedWord.tokenValue == ")")
				{
					current = _getNext();
					if (current.taggedWord.tokenValue == ";")
					{
						// Valid syntax for object construction. Add to block and return true.
						_activeBlock->addNode(toUse);
						return new Node(Node::NodeDetails(nullptr, 0, 0));
					}
				}
				else
				{
					//Error, unexpected symbol
				}
			}

			// Next part must be a ) symbol.
			current = _getNext();
			if (current.taggedWord.tokenValue == "{")
			{

			}

		}
		else if (current.taggedWord.tokenValue == ";")
		{
			//Third case confirmed.
			// [TYPE/CLASS] [IDENTIFIER] ;
			Symbol newSymbol(stack.at(1).taggedWord.tokenValue, _activeBlock, toUse);

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
		// Must be Rule 4 (Assignment OP), next must evaluate to valid expression.
        printf("op called\n");
		Node* rightOperand = _validateExpression();
		Node* newNode = new Assignment(toUse, rightOperand, Node::NodeDetails(_activeBlock, current.taggedWord.tokenType, current.line));
		_activeBlock->addNode(newNode);
	}
	else
	{
		// Throw an error.
	}
}

//Function Parameters:
// TYPE IDENTIFIER
// TYPE IDENTIFIER , IDENTIFIER ...
std::vector<FunctionParameter> Validator::_validateFunctionParameters()
{
	TaggedLexeme current = (*_it);
	return std::vector<FunctionParameter>();
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

// FOR ( EXPR ; EXPR ; EXPR ) {
For* Validator::_validateFor()
{
	// Only allow iterative controls.
	// Must follow syntax:
	// FOR ( EXPR; EXPR; EXPR) {
	// where the expressions must be null or (in order):
	// 1) type declaration/definition
	// 2) boolean checkable expression
	// 3) identifier iteration
	TaggedLexeme current = (*_it);
	return nullptr;
}

// WHILE ( BOOL_EXPR ) {
While* Validator::_validateWhile()
{
	TaggedLexeme current = (*_it);
	return nullptr;
}

// if ( bool_expr ) {
If* Validator::_validateIf()
{
	TaggedLexeme current = (*_it);
	return nullptr;
}

Node* Validator::_validateStatement()
{
	TaggedLexeme tag = (*_it);
	Node* toReturn = nullptr;
	if (tag.taggedWord.tokenValue == "if")
	{
		toReturn = _validateIf();
	}
	else if (tag.taggedWord.tokenValue == "for")
	{
		toReturn = _validateFor();
	}
	else if (tag.taggedWord.tokenValue == "while")
	{
		toReturn = _validateWhile();
	}
	else if (tag.taggedWord.tokenValue == "break")
	{
		if(_isInLoop())
			_activeBlock->addNode(new Break(Node::NodeDetails(_activeFunction, tag.taggedWord.tokenType, tag.line)));
		else BreakNotInLoop(tag.line, __FILE__);
	}
	else if (tag.taggedWord.tokenValue == "continue")
	{
		if (_isInLoop())
			_activeBlock->addNode(new Continue(Node::NodeDetails(_activeFunction, tag.taggedWord.tokenType, tag.line)));
		else ContinueNotInLoop(tag.line, __FILE__);
	}
	else
	{
		UnexpectedToken(tag.line, __FILE__, tag.taggedWord.tokenValue);
	}
	return toReturn;
}

// class [identifer] {
Class* Validator::_validateClass()
{
	auto tag = _getNext();
	if (_nestingLevel > 0)
		ImbalancedBraces(tag.line, __FILE__);

	//_activeclass = new class(tag.taggedWord.tokenValue);
	if (tag.taggedWord.tokenType != TokenTypes::IDENTIFIER)
		NotValidWord(tag.line, __FILE__, tag.taggedWord.tokenValue);
	tag = _getNext();

	if (tag.taggedWord.tokenType != TokenTypes::SYMBOL || tag.taggedWord.tokenValue != "{")
		InvalidClassBraces(tag.line, __FILE__);
	_nestingLevel++;





	return nullptr;
}

// should evaluate to:
// [ident] [op] [value]
// where [value] can be another nested expression.
// e.g.
// [ident] [op] [ident] [op] [ident] [op] [value] ;
// a        =      b     +      c     *    2      ;
// a        =   (  b     +   (  c     *    2    ));
//
//                    [op]
//                   /    \
//            [ident]      [op]
//                        /    \
//                 [ident]      [op]
//                             /    \
//                      [ident]      [value]
//
// except in case of function call. which must be:
// variable_ident . function_name( function_params_expr ) ;
// or
// function_name ( function_params_expr ) ;
Node* Validator::_validateExpression()
{
	TaggedLexeme current = (*_it);
	if (current.taggedWord.tokenType == TokenTypes::OPERATOR)
    {

    }

	return nullptr;
}

bool Validator::_validateSymbol()
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
					NotExpectedParentPointerType(current.line, __FILE__, "Block");
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
	else if (current.taggedWord.tokenValue == "{")
	{
		//Should never occur section.
		UnexpectedSymbol(current.line, __FILE__, '{');
		_nestingLevel++;
	}
}

bool Validator::_validateSyntax()
{
	do
	{
		TaggedLexeme current = (*_it);
		if (current.taggedWord.tokenValue == "class")
		{
			Class* newClass = _validateClass();
			if (_activeClass == nullptr)
			{
				_activeClass = newClass;
			}
		}
		else if (current.taggedWord.tokenType == TokenTypes::KEYWORD)
		{
			Node* statement = _validateStatement();
		}
		else if (current.taggedWord.tokenType == TokenTypes::TYPE)
		{
			Node* type = _validateType();
		}
		else if (current.taggedWord.tokenType == TokenTypes::IDENTIFIER)
		{
			Node* expression = _validateExpression();
		}
		else if (current.taggedWord.tokenType == TokenTypes::SYMBOL)
		{
			_validateSymbol();
		}
	} while (++_it != _tokens.end());

	return true;
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

void Validator::addTags(taglist tags)
{
	_tokens = tags;
    _it = _tokens.begin();
}

void Validator::_resetPrivateData()
{
	_nestingLevel = 0;
	taglist _tokens = taglist();
	tagIt _it = tagIt();
	RootNode _rootNode = RootNode();
	Class* _activeClass = nullptr;
	Block* _activeBlock = nullptr;
	Function* _activeFunction = nullptr;
}

bool Validator::buildTree()
{
	if (_tokens.size() > 0)
	{
		_validateSyntax();
	}
	else
	{
		NoLexemesFound(0, __FILE__);
	}



	return true;
}

bool Validator::buildTree(taglist tags)
{
	_tokens = tags;
	if (_tokens.size() > 0)
	{
		_validateSyntax();
	}
	else
	{
		NoLexemesFound(0, __FILE__);
	}

	return true;
};
