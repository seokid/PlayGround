#include "CBaekjoon.h"


//9663��
//N-Queen
//ũ�Ⱑ N �� N�� ü���� ���� �� N���� ���� ������ �� ���� ���� ����� �� ����
//DFS + Backtracking�� �̿��Ͽ� Ǯ��

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
		if (N_Queen_Check(y))	//��ȿ�� �̵����� Ȯ��
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

//17608��
//�����
//����⸦ �Ϸķ� ���� �����ʿ��� ������ ���̴� ������� ������ ����϶�
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


//17609��
//ȸ��
//ȸ�� : �� �ڹ������� �� �� ���� ������ ���ڷ� ������ ���ڿ�
//����ȸ�� : �� ���ڸ� �����ϸ� ȸ���� �Ǵ� ���ڿ�
//ȸ�� : 0, ����ȸ�� : 1, �� �� : 2 �� ����϶�

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
