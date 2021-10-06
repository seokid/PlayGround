#include "CHackerRank.h"
#include <algorithm>
#include <stack>
#include <map>
#include <unordered_map>
#include <iostream>

//Reverse Shuffle Merge
//다음과 같은 규칙으로 합쳐진 문자열의 원본 문자열을 반환해라
//Merge(reverse(A), shuffle(A);
//reverse : 뒤집기
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

	std::copy(arrCheck, arrCheck + iSize, arrExcept);
	
	std::stack<char> st;
	

	// reverse 되어있기 때문에 반대로 찾는다.
	for (int i = (int)s.size() - 1; 0 <= i; --i)
	{
		
		while (!st.empty() && st.top() > s[i]	//자신이 더 앞에 와야함
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


//Hash Tables: Ice Cream Parlor
//아이스크림 가게에서 2가지의 맛 중 돈에 맞게 살수있는 맛을 선택해서 오름차순으로 출력
//ex) money = 4, cost = [1, 4, 5, 3, 2], answer = 1, 4
void CHackerRank::whatFlavors(vector<int> cost, int money) 
{
	std::unordered_map<int, int> map;

	//비용을 키 값으로 인덱스와 함께 등록
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
