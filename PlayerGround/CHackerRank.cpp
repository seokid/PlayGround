#include "CHackerRank.h"


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
			map[cost[i]] = (int)i;
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


//Maximum Subarray Sum
//부분합을 이용하여 가장 큰 나머지 값을 반환하라

long CHackerRank::maximumSum(vector<long> a, long m)
{
	long answer = 0l;
	long Sum = 0l;

	set<long> st;
	for (size_t i = 0; i < a.size(); ++i)
	{
		Sum = (Sum + a[i]) % m;	//누적
		answer = max(answer, Sum);
		set<long>::iterator iter = st.lower_bound(Sum + 1);	//lower_bound가 같거나 큰 값이기 때문에 무조건 큰값만 찾아야해서 + 1
															//지금까지 누적된 결과 중 자신보다 큰 값을 찾는다.(이 값을 시작으로 자기 기준 최대 부분 누적합)
		if (st.end() != iter)
		{
			answer = max(answer, (Sum - *iter + m) % m);	//(누적합 - 시작합 + m(음수로 넘어갈수있기때문에 더해준다 어처피 나머지를 사용하기때문에 지장없음)) % m
		}
		st.insert(Sum);
	}

	return answer;
	
}


//Max Array Sum
//누적합을 이용하여 최대 값 찾기
//음수일 경우 0을 리턴
int CHackerRank::maxSubsetSum(vector<int> arr)
{
	// 초기 셋팅을 0으로 해서 최대 값을 0으로 리턴
	arr[0] = max(arr[0], 0);
	arr[1] = max(arr[1], 0);

	if (2 < arr.size())
	{
		if (0 < arr[2])
			arr[2] += arr[0];
		else
			arr[2] = arr[0];
	}

	for (size_t i = 3; i < arr.size(); ++i)
	{
		//자신이 음수라면 이전 누적합을 그대로 사용한다(자신을 건너뜀)
		int Max = max(arr[i - 2], arr[i - 3]);
		if (0 < arr[i])
			arr[i] += Max;
		else
			arr[i] = Max;
	}

	return *max_element(arr.begin(), arr.end());
}
