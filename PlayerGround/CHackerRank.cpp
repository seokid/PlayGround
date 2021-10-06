#include "CHackerRank.h"
#include <algorithm>
#include <stack>

//Reverse Shuffle Merge
//다음과 같은 규칙으로 합쳐진 문자열의 원본 문자열을 반환해라
//Merge(revers(A), shuffle(A);
//revers : 뒤집기
//shuffle : 섞기
//Merge : 두 문자를 사전순으로 가장작게 합쳐준다
//ex) intput : abcdefgabcdefg, output : agfedcb
string CHackerRank::reverseShuffleMerge(string s)
{
	string strAnswer = "";
	const int iSize = 'z' - 'A' + 1;
	int arrCheck[iSize] = {};
	int arrExcept[iSize] = {};
	
	for (size_t i = 0; i < s.size(); ++i)
	{
		++arrCheck[s[i] - 'A'];
	}
	
	// 중복되어 들어가있어서 나누어준다
	for (int i = 0; i < iSize; ++i)
	{
		arrCheck[i] /= 2;
	}

	copy(arrCheck, arrCheck + iSize, arrExcept);
	
	stack<char> st;
	

	// reverse 되어있기 때문에 반대로 찾는다.
	for (int i = (int)s.size() - 1; 0 <= i; --i)
	{
		while (!st.empty() && st.top() > s[i] 
			&& arrCheck[s[i] - 'A'] > 0
			&& arrExcept[st.top() - 'A'] > 0)
		{
			//제외로 옮겨준다
			char c = st.top();
			st.pop();
			++arrCheck[c - 'A'];
			--arrExcept[c - 'A'];
		}

		if (0 < arrCheck[s[i] - 'A'])
		{
			st.push(s[i]);
			--arrCheck[s[i] - 'A'];
		}
		else
		{
			--arrExcept[s[i] - 'A'];
		}
	}

	while (!st.empty()) {
		strAnswer = st.top() + strAnswer;
		st.pop();
	}

	return strAnswer;
}