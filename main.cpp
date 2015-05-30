#include "Regex.h"

using namespace std;

int main()
{
	vector<string> s;
	
	s.push_back("aaaabccccbbbcc");
	s.push_back("defg");
	s.push_back("dex");
	s.push_back("dexz");
	s.push_back("fwwaaaaacccbbbcbcbdcc");
	

	Regex rgx("a+[bc]*|de(fg|x[yz]?)*");

	for (int i = 0; i < s.size(); i++)
	{
		if (rgx.contains(s[i]))
		{
			cout << "yes" << endl;
			cout << "matched string: \"" << rgx.group(0) << "\"" << endl;
			for (int i = 1; i < rgx.matchGroupsCount(); i++)
				cout << "captured group " << i << ": \"" << rgx.group(i) << "\"" << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		else
		{
			cout << "no" << endl;
		}
	}

	system("pause");
	return 0;
}