#include "ParseString.h"




char ParseString::peek()
{
	if (current >= source.size()) throw ParseError();
	return source[current];
}

char ParseString::get()
{
	if (current >= source.size()) throw ParseError("");
	return source[current++];
}

void ParseString::reset()
{
	current = 0;
}

void ParseString::moveBack()
{
	if (current > 0) current--;
}

void ParseString::moveForward()
{
	if (current < source.size()) current++;
}

ParseString::ParseString(const string& source)
{
	this->source = source;
	current = 0;
}

int ParseString::getCurrent() const
{
	return current;
}

void ParseString::setCurrent(int current)
{
	this->current = current;
}

bool ParseString::isDone()
{
	return (current >= source.size());
}
