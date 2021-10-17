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