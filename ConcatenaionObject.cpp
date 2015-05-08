#include "ConcatenaionObject.h"
#include "Regex.h"


void ConcatenationObject::parse(Regex* rgx)
{
	char c = rgx->src.peek();
	while (c != '|' && c != ')')
	{
		QuantifiedRegexObject* object = new QuantifiedRegexObject;
		object->parse(rgx);
		objectsList.push_back(object);
		c = rgx->src.peek();
	}
	if(rgx->src.peek() == '|') rgx->src.get();
}

ConcatenationObject::~ConcatenationObject()
{
	for (int i = 0; i < objectsList.size(); i++)
		delete objectsList[i];
	objectsList.clear();
}

ConcatenationObject& ConcatenationObject::operator=(const ConcatenationObject& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < objectsList.size(); i++)
			delete objectsList[i];
		objectsList.clear();

		matched = rhs.matched;
		capturedRange = rhs.capturedRange;
		for (int i = 0; i < rhs.objectsList.size(); i++)
			objectsList.push_back(new QuantifiedRegexObject(*rhs.objectsList[i]));
	}
	return *this;
}

ConcatenationObject::ConcatenationObject(const ConcatenationObject& rhs)
{
	matched = rhs.matched;
	capturedRange = rhs.capturedRange;
	for (int i = 0; i < rhs.objectsList.size(); i++)
		objectsList.push_back(new QuantifiedRegexObject(*rhs.objectsList[i]));
}

ConcatenationObject::ConcatenationObject()
{
	matched = false;
	capturedRange = make_pair(-1, -1);
}

bool ConcatenationObject::matches(Regex* rgx)
{
	int cursor = rgx->matchString.getCurrent();

	for (int i = 0; i < objectsList.size(); i++)
	{
		if (!objectsList[i]->matches(rgx))
		{
			rgx->matchString.setCurrent(cursor);
			return false;
		}
	}
	matched = true;
	capturedRange = make_pair(cursor, rgx->matchString.current);
	return true;
}
