#pragma once
#include "QuantifiedRegexObject.h"

class Regex;
class ConcatenationObject
{
	vector<QuantifiedRegexObject*> objectsList;
	pair<int, int> capturedRange;
	bool matched;

public:
	ConcatenationObject();

	ConcatenationObject(const ConcatenationObject& rhs);

	ConcatenationObject& operator=(const ConcatenationObject& rhs);

	~ConcatenationObject();

	void parse(Regex* source);

	bool matches(Regex* rgx);
};