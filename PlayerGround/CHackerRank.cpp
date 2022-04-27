#include "CHackerRank.h"


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
//���� Ʈ�� ���� �� ���� ��ȸ ���
//���̰� ���� ������ ������ �������� ��� ����
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


	//�޸� ����
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
//�κ����� �̿��Ͽ� ���� ū ������ ���� ��ȯ�϶�

long CHackerRank::maximumSum(vector<long> a, long m)
{
	long answer = 0l;
	long Sum = 0l;

	set<long> st;
	for (size_t i = 0; i < a.size(); ++i)
	{
		Sum = (Sum + a[i]) % m;	//����
		answer = max(answer, Sum);
		set<long>::iterator iter = st.lower_bound(Sum + 1);	//lower_bound�� ���ų� ū ���̱� ������ ������ ū���� ã�ƾ��ؼ� + 1
															//���ݱ��� ������ ��� �� �ڽź��� ū ���� ã�´�.(�� ���� �������� �ڱ� ���� �ִ� �κ� ������)
		if (st.end() != iter)
		{
			answer = max(answer, (Sum - *iter + m) % m);	//(������ - ������ + m(������ �Ѿ���ֱ⶧���� �����ش� ��ó�� �������� ����ϱ⶧���� �������)) % m
		}
		st.insert(Sum);
	}

	return answer;
	
}


//Max Array Sum
//�������� �̿��Ͽ� �ִ� �� ã��
//������ ��� 0�� ����
int CHackerRank::maxSubsetSum(vector<int> arr)
{
	// �ʱ� ������ 0���� �ؼ� �ִ� ���� 0���� ����
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
		//�ڽ��� ������� ���� �������� �״�� ����Ѵ�(�ڽ��� �ǳʶ�)
		int Max = max(arr[i - 2], arr[i - 3]);
		if (0 < arr[i])
			arr[i] += Max;
		else
			arr[i] = Max;
	}

	return *max_element(arr.begin(), arr.end());
}
