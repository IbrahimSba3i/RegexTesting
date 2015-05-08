#pragma once
#include "ConcatenaionObject.h"

class Regex;
class Expression
{
	vector<ConcatenationObject*> objectsList;
	bool isCapturingGroup;


public:
	Expression();

	Expression(const Expression& rhs);

	Expression& operator=(const Expression& rhs);
	
	~Expression();

	void parse(Regex* rgx);

	bool matches(Regex* rgx);
};