#include "Regex.h"

using namespace std;

int main()
{
	vector<string> s;
	
	s.push_back("aaaabccccbbbcc");
	s.push_back("defg");
	s.push_back("dex");
	s.push_back("dexz");
	s.push_back("aaaaacccbbbcbcbdcc");
	

	Regex rgx("a+[bc]*|de(fg|x[yz]?)*");

	for (int i = 0; i < s.size(); i++)
	{
		if (rgx.matches(s[i]))
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}

	system("pause");
	return 0;
}