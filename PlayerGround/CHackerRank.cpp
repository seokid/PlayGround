#include "CHackerRank.h"
#include <algorithm>
#include <stack>
#include <map>
#include <unordered_map>
#include <iostream>

//Reverse Shuffle Merge
//������ ���� ��Ģ���� ������ ���ڿ��� ���� ���ڿ��� ��ȯ�ض�
//Merge(reverse(A), shuffle(A);
//reverse : ������
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

	std::copy(arrCheck, arrCheck + iSize, arrExcept);
	
	std::stack<char> st;
	

	// reverse �Ǿ��ֱ� ������ �ݴ�� ã�´�.
	for (int i = (int)s.size() - 1; 0 <= i; --i)
	{
		
		while (!st.empty() && st.top() > s[i]	//�ڽ��� �� �տ� �;���
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


//Hash Tables: Ice Cream Parlor
//���̽�ũ�� ���Կ��� 2������ �� �� ���� �°� ����ִ� ���� �����ؼ� ������������ ���
//ex) money = 4, cost = [1, 4, 5, 3, 2], answer = 1, 4
void CHackerRank::whatFlavors(vector<int> cost, int money) 
{
	std::unordered_map<int, int> map;

	//����� Ű ������ �ε����� �Բ� ���
	for (size_t i = 0; i < cost.size(); ++i)
	{
		if (money > cost[i])
			map[cost[i]] = i;
	}

	for (size_t i = 0; i < cost.size(); ++i)
	{
		int iPrice = money - cost[i];
		auto pair = map.find(iPrice);
		if (pair != map.end())
		{
			if (i + 1 == pair->second + 1)
				continue;

			cout << i + 1 << " " << pair->second + 1 << endl;
			return;
		}
	}
}
