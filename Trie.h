#ifndef TRIE_H
#define TRIE_H
#include <vector>
#include <string>
using namespace std;

template <class Type>
class Trie
{
private:
	class Data
	{
	public:
		Type data;
	};
	class element
	{
	public:
		bool isEnd;
		int prefixCount;
		int childrenIndex;
		Data* data;
		element(){ isEnd = false; prefixCount = 0; childrenIndex = -1; data = NULL; }
	};
	element root;
	vector< vector<element> > children;
public:
	void insert(string s, const Type& insertionData)
	{
		element *l = &root;
        for (unsigned int i = 0; i < s.size(); i++){
			if (l->childrenIndex == -1){
				children.push_back(vector<element>(26));
				l->childrenIndex = children.size() - 1;
			}
			l->prefixCount++;
			l = &children[l->childrenIndex][s[i] - 'a'];
		}
		l->prefixCount++; //
		l->isEnd = true;
		l->data = new Data;
		l->data->data = insertionData;
	}
	Type getData(string s)
	{
		element *l = &root;
		for (unsigned int i = 0; i < s.size(); i++){
			if (l->childrenIndex == -1)
				return false;
			l = &children[l->childrenIndex][s[i] - 'a'];
		}
		if (!l->isEnd)
			throw logic_error("string key not found");
		return l->data->data;
	}

	bool search(string s)
	{
		element *l = &root;
        for (unsigned int i = 0; i < s.size(); i++){
			if (l->childrenIndex == -1)
				return false;
			l = &children[l->childrenIndex][s[i] - 'a'];
		}
		return l->isEnd;
	}

	void remove(string s)
	{
		element *l = &root;
		for (unsigned int i = 0; i < s.size(); i++){
			if (l->childrenIndex == -1)
				throw logic_error("string key not found");
			l = &children[l->childrenIndex][s[i] - 'a'];
		}
		l->isEnd = false;
		delete l->data;
		l->data = NULL;
		//return l->isEnd;
	}

	int wordsWithPrefix(string s)
	{
		element *l = &root;
        for (unsigned int i = 0; i < s.size(); i++){
			if (l->childrenIndex == -1)
				return 0;
			l = &children[l->childrenIndex][s[i] - 'a'];
		}
		return l->prefixCount;
	}

	~Trie()
	{
		for (int i = 0; i < children.size(); i++){
			for (int j = 0; j < children[i].size(); j++){
				if (children[i][j].data != NULL) delete children[i][j].data;
			}
		}
	}
};

#endif
