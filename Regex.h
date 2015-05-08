#pragma once
#include "ParseString.h"
#include "Expression.h"

class Regex
{
	std::string value;
	
	vector<string> matchGroups;
	
	ParseString src;
	ParseString matchString;
	bool compiled;

	friend class Expression;
	friend class QuantifiedRegexObject;
	friend class RegexObject;
	friend class ConcatenationObject;
	friend class Utility;
	friend class CharacterSet;
	
	Expression exp;

	void parse()
	{
		try
		{
			src.source = "(" + src.source + ")";
			exp.parse(this);
		}
		catch (ParseError& e)
		{
			cout << "ParseError: " << e.what() << endl;
		}
		catch (std::exception& e)
		{
			cout << e.what() << endl;
		}
	}

public:

	Regex() : src(""), matchString("")
	{
		compiled = false;
	}

	Regex(const string& source) : src(""), matchString("")
	{
		compile(source);
	}

	void compile(const string& src)
	{
		value = src;
		compiled = true;
		this->src = src;
		parse();
	}

	bool matches(const string& other)
	{
		if (!compiled) throw exception("");
		matchString = other;
		return exp.matches(this) && matchString.isDone();
	}
};