#include "utility.h"
#include "Regex.h"

bool Utility::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

int Utility::parseInt(Regex* rgx)
{
	int val = 0;
	char c;
	while (isDigit(c = rgx->src.peek()))
	{
		val = val * 10 + (c - int('0'));
		rgx->src.get();
	}
	return val;
}

char Utility::getEquivalentCharacter(char c)
{
	map<char, char> getEquivalent;
	getEquivalent['n'] = '\n';
	getEquivalent['r'] = '\r';
	getEquivalent['t'] = '\t';
	getEquivalent['a'] = '\a';
	getEquivalent['e'] = '\e';
	getEquivalent['f'] = '\f';
	getEquivalent['v'] = '\v';
	getEquivalent['B'] = '\\';
	getEquivalent['0'] = '\0';

	if (getEquivalent.count(c))
		return getEquivalent[c];
	else return c;
}


