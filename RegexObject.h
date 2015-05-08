#pragma once
#include "CharacterSet.h"


enum class RegexObjectType
{
	CHARACTER,
	CHARACTER_SET,
	EXPRESSION
};

class Expression;
class Regex;
class RegexObject
{
	char value;
	CharacterSet* charSet;
	Expression* expression;
	RegexObjectType type;

public:

	RegexObject();

	RegexObject(const RegexObject& rhs);

	~RegexObject();

	RegexObject& operator=(const RegexObject& rhs);

	void parse(Regex* source);

	bool matches(Regex* rgx);
};