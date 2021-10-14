#include "CHackerRank.h"
#include <algorithm>
#include <stack>
#include <queue>
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


//Swap Nodes [Algo]
//이진 트리 스왑 후 중위 순회 출력
//깊이가 스왑 값으로 나누어 떨어지는 경우 스왑
struct tSwapNode
{
	int     Value;
	tSwapNode*  Left;
	tSwapNode*  Right;
};

void swapNode_DFS(tSwapNode* Parent, vector<int>& Result)
{
	if (-1 == Parent->Value)
		return;

	swapNode_DFS(Parent->Left, Result);
	Result.push_back(Parent->Value);
	swapNode_DFS(Parent->Right, Result);
}

void swapNode_Swap(tSwapNode* Parent, int Swap, int Depth)
{
	if (-1 == Parent->Value)
		return;

	if (0 == Depth % Swap)
	{
		tSwapNode* Tmp = Parent->Left;
		Parent->Left = Parent->Right;
		Parent->Right = Tmp;
	}

	swapNode_Swap(Parent->Left, Swap, Depth + 1);
	swapNode_Swap(Parent->Right, Swap, Depth + 1);
}

vector<vector<int>> CHackerRank::swapNodes(vector<vector<int>> indexes, vector<int> queries) {
	vector<vector<int>> Answer;
	int Idx = 0;
	queue<tSwapNode*> que;
	tSwapNode* RootNode = new tSwapNode{ 1, nullptr, nullptr };
	que.push(RootNode);

	while (Idx < indexes.size())
	{
		tSwapNode* ParentNode = que.front();
		que.pop();

		if (-1 == ParentNode->Value)
			continue;

		ParentNode->Left = new tSwapNode{ indexes[Idx][0], nullptr, nullptr };
		ParentNode->Right = new tSwapNode{ indexes[Idx][1], nullptr, nullptr };
		++Idx;

		que.push(ParentNode->Left);
		que.push(ParentNode->Right);
	}

	for (size_t i = 0; i < queries.size(); ++i)
	{
		swapNode_Swap(RootNode, queries[i], 1);

		vector<int> Result;
		swapNode_DFS(RootNode, Result);
		Answer.push_back(Result);
	}


	//메모리 해제
	que = queue<tSwapNode*>();
	que.push(RootNode);
	while (!que.empty())
	{
		tSwapNode* ParentNode = que.front();
		que.pop();

		if (-1 == ParentNode->Value)
			continue;

		que.push(ParentNode->Left);
		que.push(ParentNode->Right);

		delete ParentNode;
	}

	return Answer;
}