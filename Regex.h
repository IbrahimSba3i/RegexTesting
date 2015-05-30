#pragma once
#include "ParseString.h"
#include "Expression.h"
#include <algorithm>

class Regex
{
	std::string value;
	
	vector<pair<int, int> > matchedRanges;
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
		
		matchGroups.clear();
		matchedRanges.clear();

		bool result = exp.matches(this) && matchString.isDone();

		sort(matchedRanges.begin(), matchedRanges.end());
		for (int i = 0; i < matchedRanges.size(); i++)
			matchGroups.push_back(other.substr(matchedRanges[i].first, -matchedRanges[i].second));

		return result;
	}

	size_t search(const string& other)
	{
		if (!compiled) throw exception("");
		matchString = other;
		matchGroups.clear();

		for (int i = 0; i < other.length(); i++)
		{
			matchedRanges.clear();
			matchString.setCurrent(i);
			if (exp.matches(this))
			{
				sort(matchedRanges.begin(), matchedRanges.end());
				for (int i = 0; i < matchedRanges.size(); i++)
					matchGroups.push_back(other.substr(matchedRanges[i].first, -matchedRanges[i].second));
				return i;
			}
		}
		return string::npos;
	}

	bool contains(const string& other)
	{
		return (search(other) != string::npos);
	}

	int matchGroupsCount() const
	{
		return matchGroups.size();
	}

	const string& group(size_t index = 0) const
	{
		if (index >= matchGroups.size())
			throw out_of_range("Match group out of range");
		return matchGroups[index];
	}

	const string& cap(size_t index = 0) const
	{
		return group(index);
	}

	const string& operator[](size_t index) const
	{
		return group(index);
	}
};