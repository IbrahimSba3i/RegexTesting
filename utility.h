#pragma once
#include "GlobalIncludes.h"

class Regex;
class Utility
{
public:
	static int parseInt(Regex* rgx);
	static bool isDigit(char c);
	static char getEquivalentCharacter(char c);
};

