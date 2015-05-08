#include "QuantifiedRegexObject.h"
#include "Regex.h"




QuantifiedRegexObject::QuantifiedRegexObject()
{
	type = QuantifierType::NONE;
	greedy = true;
	regexObject = NULL;
	range = make_pair(-1, -1);
}

QuantifiedRegexObject::QuantifiedRegexObject(const QuantifiedRegexObject& rhs)
{
	type = rhs.type;
	greedy = rhs.greedy;
	range = rhs.range;
	if (rhs.regexObject != NULL)
		regexObject = new RegexObject(*rhs.regexObject);
	else regexObject = NULL;
}

void QuantifiedRegexObject::parse(Regex* rgx)
{
	regexObject = new RegexObject;
	regexObject->parse(rgx);
	char c = rgx->src.peek();
	if (c == '+' || c == '*' || c == '?')
	{
		rgx->src.get();
		if (c == '+') type = QuantifierType::KLEENE_PLUS;
		else if (c == '*') type = QuantifierType::KLEENE_STAR;
		else type = QuantifierType::QUESTION_MARK;
		if (rgx->src.peek() == '?')
		{
			greedy = false;
			rgx->src.get();
		}
	}
	else if (c == '{')
	{
		char x;
		int minVal, maxVal;
		minVal = Utility::parseInt(rgx);
		if (rgx->src.get() != ',')
		{
			rgx->src.moveBack();
			maxVal = minVal;
		}
		else
		{
			if (Utility::isDigit(rgx->src.peek()))
			{
				maxVal = Utility::parseInt(rgx);
			}
			else
			{
				maxVal = oo;
			}
		}
		
		if (rgx->src.get() != '}') throw ParseError("");
		if (maxVal < minVal) swap(minVal, maxVal);
		range = make_pair(minVal, maxVal);
		type = QuantifierType::RANGED;
	}
}

QuantifiedRegexObject::~QuantifiedRegexObject()
{
	if (regexObject) delete regexObject;
}

QuantifiedRegexObject& QuantifiedRegexObject::operator=(const QuantifiedRegexObject& rhs)
{
	if (this != &rhs)
	{
		if (regexObject) delete regexObject;

		type = rhs.type;
		greedy = rhs.greedy;
		range = rhs.range;
		if (rhs.regexObject != NULL)
			regexObject = new RegexObject(*rhs.regexObject);
		else regexObject = NULL;
	}

	return *this;
}

bool QuantifiedRegexObject::matches(Regex* rgx)
{
	try{
		if (type == QuantifierType::NONE)
		{
			return regexObject->matches(rgx);
		}
		else if (type == QuantifierType::KLEENE_PLUS)
		{
			if (!regexObject->matches(rgx)) return false;
			while (!rgx->matchString.isDone() && regexObject->matches(rgx));
			return true;
		}
		else if (type == QuantifierType::KLEENE_STAR)
		{
			while (!rgx->matchString.isDone() && regexObject->matches(rgx));
			return true;
		}
		else if (type == QuantifierType::QUESTION_MARK)
		{
			regexObject->matches(rgx);
			return true;
		}
		else if (type == QuantifierType::RANGED)
		{
			int x = 0;
			while (!rgx->matchString.isDone() && regexObject->matches(rgx)) x++;
			if (x > range.second || x < range.first) return false;
			else return true;
		}
	}
	catch (...){}
	return true;
}
