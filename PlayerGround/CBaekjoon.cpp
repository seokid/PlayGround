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