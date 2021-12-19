#include "CBaekjoon.h"


//9663번
//N-Queen
//크기가 N × N인 체스판 위에 퀸 N개를 서로 공격할 수 없게 놓는 경우의 수 문제
//DFS + Backtracking을 이용하여 풀이

int N_Queen_Check_arrChess[14];
int N_Queen_Check_answer;

bool N_Queen_Check(int y)
{
	for (int i = 0; i < y; ++i)
	{
		if (N_Queen_Check_arrChess[y] == N_Queen_Check_arrChess[i] || abs(N_Queen_Check_arrChess[y] - N_Queen_Check_arrChess[i]) == y - i)
			return false;
	}
	return true;
}

void N_Queen_DFS(int y, int n)
{
	if (n == y)
		++N_Queen_Check_answer;

	for (int i = 0; i < n; ++i)
	{
		N_Queen_Check_arrChess[y] = i;
		if (N_Queen_Check(y))	//유효한 이동인지 확인
			N_Queen_DFS(y + 1, n);
	}
}

void CBaekjoon::N_Queen()
{
	int n;

	cin >> n;

	N_Queen_DFS(0, n);

	cout << N_Queen_Check_answer << endl;
}


bool cmp(pair<int, int> Left, pair<int, int> Right)
{
	if (Left.first == Right.first)
	{
		return Left.second > Right.second;
	}
	return Left.first > Right.first;
}

//17608번
//막대기
//막대기를 일렬로 세워 오른쪽에서 봤을때 보이는 막대기의 개수를 출력하라
void CBaekjoon::Bar()
{

	int n, h, answer = 0;
	cin >> n;

	stack<int> st;

	for (int i = 0; i < n ; ++i)
	{
		cin >> h;
		st.push(h);
	}


	int Max = 0;
	while (!st.empty())
	{
		if (Max < st.top())
		{
			Max = st.top();
			++answer;
		}
		st.pop();
	}

	/*vector<int>::iterator end = vec.end();

	while (end != vec.begin())
	{
		end = max_element(vec.begin(), end);
		++answer;
	}*/

	cout << answer << endl;
}


//17609번
//회문
//회문 : 앞 뒤방향으로 볼 때 같은 순서의 문자로 구성된 문자열
//유사회문 : 한 문자를 삭제하면 회문이 되는 문자열
//회문 : 0, 유사회문 : 1, 그 외 : 2 를 출력하라

int IsPalindrome(int head, int tail, const string& str, int depth)
{
	if (1 < depth)
		return 2;

	while (head < tail)
	{
		if (str[head] != str[tail])
		{
			return min(IsPalindrome(head + 1, tail, str, depth + 1), IsPalindrome(head, tail - 1, str, depth + 1));
		}
		++head;
		--tail;
	}
	return depth;
}

void CBaekjoon::Palindrome()
{
	int n;
	
	cin >> n;

	vector<string> vec(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> vec[i];
	}

	for (size_t i = 0; i < vec.size(); ++i)
	{
		cout << IsPalindrome(0, vec[i].size() - 1, vec[i], 0) << endl;
	}

}
