#pragma once
#include "GlobalIncludes.h"

class Regex;
class CharacterSet
{
private:
	bitset<256> characterExists;

public:

	CharacterSet();
	CharacterSet(char c);
	void insertCharacter(char c);
	void removeCharacter(char c);
	void fillAll();
	void clearAll();
	void insertAll(const string& s);
	void removeAll(const string& s);
	bool contains(char c);
	void parse(Regex* rgx);
};