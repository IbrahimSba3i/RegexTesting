#pragma once
#include "GlobalIncludes.h"
#include "ParseError.h"

class ParseString
{
public:
	string source;
	int current;
	int getCurrent() const;
	void setCurrent(int current);
	ParseString(const string& source);

	void moveForward();

	void moveBack();

	void reset();

	char get();

	char peek();

	bool isDone();
};