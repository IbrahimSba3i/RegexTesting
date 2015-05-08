#pragma once
#include "RegexObject.h"
#include "utility.h"

enum class QuantifierType
{
	KLEENE_PLUS,
	KLEENE_STAR,
	QUESTION_MARK,
	RANGED,
	NONE
};

class Regex;
class QuantifiedRegexObject
{
	RegexObject* regexObject;
	QuantifierType type;
	bool greedy;
	pair<int, int> range;

public:
	QuantifiedRegexObject();

	QuantifiedRegexObject(const QuantifiedRegexObject& rhs);

	QuantifiedRegexObject& operator= (const QuantifiedRegexObject& rhs);

	~QuantifiedRegexObject();

	bool matches(Regex* rgx);

	void parse(Regex* source);
};
