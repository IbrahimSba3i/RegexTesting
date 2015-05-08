#include "Expression.h"
#include "Regex.h"



void Expression::parse(Regex* rgx)
{
	if (rgx->src.get() != '(') throw ParseError("");
	char c = rgx->src.peek();
	if (c == '?'){
		rgx->src.get();
		c = rgx->src.peek();
		if (c != ':')
		{
			rgx->src.moveBack();
		}
		else
		{
			isCapturingGroup = false;
			rgx->src.get();
		}
		c = rgx->src.peek();
	}
	while (c != ')'){
		ConcatenationObject* x = new ConcatenationObject;
		x->parse(rgx);
		objectsList.push_back(x);
		c = rgx->src.peek();
	}
}

Expression::~Expression()
{
	for (int i = 0; i < objectsList.size(); i++)
		delete objectsList[i];
	objectsList.clear();
}

Expression& Expression::operator=(const Expression& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < objectsList.size(); i++)
			delete objectsList[i];
		objectsList.clear();

		isCapturingGroup = rhs.isCapturingGroup;
		for (int i = 0; i < rhs.objectsList.size(); i++)
			objectsList.push_back(new ConcatenationObject(*rhs.objectsList[i]));
	}

	return *this;
}

Expression::Expression(const Expression& rhs)
{
	isCapturingGroup = rhs.isCapturingGroup;
	for (int i = 0; i < rhs.objectsList.size(); i++)
		objectsList.push_back(new ConcatenationObject(*rhs.objectsList[i]));
}

Expression::Expression()
{
	isCapturingGroup = true;
}

bool Expression::matches(Regex* rgx)
{
	if (objectsList.size() == 0)
	{
		return true;
	}
	for (int i = 0; i < objectsList.size(); i++)
	{
		if (objectsList[i]->matches(rgx))
		{
			return true;
		}
	}
	return false;
}
