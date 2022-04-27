#include "CStringHelper.h"

void CStringHelper::parsing(const string & page, const string & startWord, const string & endWord, vector<string>& result)
{
	size_t startIdx = page.find(startWord);
	size_t endIdx;

	while (string::npos != startIdx)
	{
		startIdx += startWord.size();
		endIdx = page.find(endWord, startIdx) - startIdx;
		result.push_back(page.substr(startIdx, endIdx));
		startIdx = page.find(startWord, startIdx + endIdx);
	}
}

void CStringHelper::split(const string & str, char ch, vector<string>& result)
{
	string tmp = "";

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (ch == str[i])
		{
			if (!tmp.empty())
				result.push_back(tmp);
			continue;
		}
		tmp += str[i];
	}

	if (!tmp.empty())
		result.push_back(tmp);
}
