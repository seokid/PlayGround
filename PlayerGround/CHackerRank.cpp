#include "CHackerRank.h"
#include <algorithm>
#include <stack>

//Reverse Shuffle Merge
//������ ���� ��Ģ���� ������ ���ڿ��� ���� ���ڿ��� ��ȯ�ض�
//Merge(revers(A), shuffle(A);
//revers : ������
//shuffle : ����
//Merge : �� ���ڸ� ���������� �����۰� �����ش�
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
	
	// �ߺ��Ǿ� ���־ �������ش�
	for (int i = 0; i < iSize; ++i)
	{
		arrCheck[i] /= 2;
	}

	copy(arrCheck, arrCheck + iSize, arrExcept);
	
	stack<char> st;
	

	// reverse �Ǿ��ֱ� ������ �ݴ�� ã�´�.
	for (int i = (int)s.size() - 1; 0 <= i; --i)
	{
		while (!st.empty() && st.top() > s[i] 
			&& arrCheck[s[i] - 'A'] > 0
			&& arrExcept[st.top() - 'A'] > 0)
		{
			//���ܷ� �Ű��ش�
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