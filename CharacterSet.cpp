#include "CharacterSet.h"
#include "Regex.h"

CharacterSet::CharacterSet()
{
	characterExists.reset();
}

CharacterSet::CharacterSet(char c)
{
	characterExists.reset();
	switch (c)
	{
	case 'd':
		for (char d = '0'; d <= '9'; d++)
			insertCharacter(d);
		break;
	case 'D':
		fillAll();
		for (char d = '0'; d <= '9'; d++)
			removeCharacter(d);
		break;
	case 'w':
		for (char d = '0'; d <= '9'; d++)
			insertCharacter(d);
		for (char d = 'a'; d <= 'z'; d++)
			insertCharacter(d);
		for (char d = 'z'; d <= 'Z'; d++)
			insertCharacter(d);
		insertCharacter('_');
		break;
	case 'W':
		fillAll();
		for (char d = '0'; d <= '9'; d++)
			removeCharacter(d);
		for (char d = 'a'; d <= 'z'; d++)
			removeCharacter(d);
		for (char d = 'z'; d <= 'Z'; d++)
			removeCharacter(d);
		removeCharacter('_');
		break;
	case 's':
		insertCharacter(' ');
		insertCharacter('\n');
		insertCharacter('\r');
		insertCharacter('\t');
		break;
	case 'S':
		fillAll();
		removeCharacter(' ');
		removeCharacter('\n');
		removeCharacter('\r');
		removeCharacter('\t');
		break;
	default:
		break;
	}
}

void CharacterSet::insertCharacter(char c)
{
	unsigned char x = c;
	characterExists[(unsigned int)x] = true;
}

void CharacterSet::removeCharacter(char c)
{
	unsigned char x = c;
	characterExists[(unsigned int)x] = false;
}

void CharacterSet::fillAll()
{
	characterExists.set();
}

void CharacterSet::clearAll()
{
	characterExists.reset();
}

void CharacterSet::insertAll(const string& s)
{
	for (int i = 0; i < s.size(); i++)
		insertCharacter(s[i]);
}

void CharacterSet::removeAll(const string& s)
{
	for (int i = 0; i < s.size(); i++)
		removeCharacter(s[i]);
}

bool CharacterSet::contains(char c)
{
	unsigned char x = c;
	return characterExists[(unsigned int)x];
}

void CharacterSet::parse(Regex* rgx)
{
	bool inv = false;
	if (rgx->src.peek() == '^')
	{
		rgx->src.get();
		fillAll();
		inv = true;
	}

	char c, t = 1;
	while ((c = rgx->src.get()) != ']')
	{
		if (c == '-')
		{
			if (t == '\0') throw ParseError("");
			else if (t == 1)
			{
				if (!inv)
					insertCharacter(c);
				else
					removeCharacter(c);
			}
			c = rgx->src.get();
			if (c == '-') throw ParseError("");
			if (t > c) swap(t, c);
			for (char x = t; x <= c; c++)
			{
				if (!inv)
					insertCharacter(x);
				else
					removeCharacter(x);
			}
			t = '\0';
		}
		else
		{
			if (c == '\\')
			{
				c = rgx->src.get();
				if (!inv)
					insertCharacter(Utility::getEquivalentCharacter(c));
				else
					removeCharacter(Utility::getEquivalentCharacter(c));
			}
			else
			{
				if (!inv)
					insertCharacter(c);
				else
					removeCharacter(c);
			}
			t = c;
		}
	}
	rgx->src.moveBack();
}