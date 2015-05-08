#include "RegexObject.h"
#include "Expression.h"
#include "Regex.h"


RegexObject::RegexObject()
{
	value = '\0';
	charSet = NULL;
	expression = NULL;
	type = RegexObjectType::CHARACTER;
}

RegexObject::RegexObject(const RegexObject& rhs)
{
	value = rhs.value;
	type = rhs.type;
	if (rhs.expression != NULL)
		expression = new Expression(*rhs.expression);
	else expression = NULL;
	if (rhs.charSet != NULL)
		charSet = new CharacterSet(*rhs.charSet);
	else charSet = NULL;
}

RegexObject::~RegexObject()
{
	if (expression != NULL) delete expression;
	if (charSet != NULL) delete charSet;
}

void RegexObject::parse(Regex* rgx)
{
	char c = rgx->src.get();
	if (c == '(')
	{
		rgx->src.moveBack();
		type = RegexObjectType::EXPRESSION;
		expression = new Expression;
		expression->parse(rgx);
		rgx->src.get();
	}
	else if (c == '[')
	{
		type = RegexObjectType::CHARACTER_SET;
		charSet = new CharacterSet;
		charSet->parse(rgx);
		rgx->src.get();
	}
	else if (c == '\\')
	{
		c = rgx->src.get();
		char C = (c >= 'a' && c <= 'z') ? c - 32 : c;
		if (C == 'D' || C == 'S' || C == 'W')
		{
			type = RegexObjectType::CHARACTER_SET;
			charSet = new CharacterSet(c);
		}
		else
		{
			type = RegexObjectType::CHARACTER;
			value = Utility::getEquivalentCharacter(c);
		}
	}
	else
	{
		type = RegexObjectType::CHARACTER;
		value = c;
	}
}

RegexObject& RegexObject::operator=(const RegexObject& rhs)
{
	if (this != &rhs)
	{
		if (expression != NULL) delete expression;
		if (charSet != NULL) delete charSet;

		value = rhs.value;
		type = rhs.type;
		if (rhs.expression != NULL)
			expression = new Expression(*rhs.expression);
		else expression = NULL;
		if (rhs.charSet != NULL)
			charSet = new CharacterSet(*rhs.charSet);
		else charSet = NULL;
	}
	return *this;
}

bool RegexObject::matches(Regex* rgx)
{
	if (type == RegexObjectType::CHARACTER)
	{
		if (value == rgx->matchString.peek())
		{
			rgx->matchString.moveForward();
			return true;
		}
		else return false;
	}
	else if (type == RegexObjectType::CHARACTER_SET)
	{
		if (charSet->contains(rgx->matchString.peek()))
		{
			rgx->matchString.moveForward();
			return true;
		}
		else return false;
	}
	else if (type == RegexObjectType::EXPRESSION)
	{
		return (expression->matches(rgx));
	}
	return true;
}
