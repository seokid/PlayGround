#pragma once

#include <string>
#include <vector>

using namespace std;

class CStringHelper
{
public:
	static void parsing(const string& page, const string& startWord, const string& endWord, vector<string>& result);
	static void split(const string& str, char ch, vector<string>& result);
};

