#include "CProgrammers.h"

#define INF 1e8

//2021 KAKAO BLIND RECRUITMENT �ս� �ý� ���
//�� ����� ��� �Ͱ��ϴ� �� �ҿ�Ǵ� ���� ���� �ýÿ�� ��ȯ, �ս� ����
//Floyd Warshall �˰����� ����Ͽ� ��� ����� �ִܰŸ��� ���Ͽ� �ּҿ�� ���
int carPool(int n, int s, int a, int b, vector<vector<int>> fares) {
	int answer = INF;
	int NodeSize = n + 1;

	vector<vector<int>> vecDist(NodeSize);
	for (int i = 1; i < NodeSize; ++i)
	{
		vecDist[i].resize(NodeSize);
		fill(vecDist[i].begin(), vecDist[i].end(), INF);
	}

	for (int i = 1; i < NodeSize; ++i)
		vecDist[i][i] = 0;

	for (size_t i = 0; i < fares.size(); ++i)
	{
		vecDist[fares[i][0]][fares[i][1]] = fares[i][2];
		vecDist[fares[i][1]][fares[i][0]] = fares[i][2];
	}

	for (int i = 1; i < NodeSize; ++i)
	{
		for (int j = 1; j < NodeSize; ++j)
		{
			for (int k = 1; k < NodeSize; ++k)
			{
				vecDist[j][k] = min(vecDist[j][k], vecDist[j][i] + vecDist[i][k]);

			}
		}
	}

	for (int i = 1; i < NodeSize; ++i)
	{
		int Cost = vecDist[s][i] + vecDist[i][a] + vecDist[i][b];
		answer = min(answer, Cost);
	}

	return answer;
}


//2021 KAKAO BLIND RECRUITMENT ���� ����
//���� ��û�� ���� �ð��뿡 ���� �����ض�
int TimeToSecond(string str)
{
	int Second = ((str[0] - '0') * 10 + str[1] - '0') * 3600
		+ ((str[3] - '0') * 10 + str[4] - '0') * 60
		+ (str[6] - '0') * 10 + str[7] - '0';
	return Second;
}

int arrViewer[360001];

string videoADInsert(string play_time, string adv_time, vector<string> logs) {

	for (size_t i = 0; i < logs.size(); ++i)
	{
		int Start = TimeToSecond(logs[i].substr(0, 8)) + 1;
		int End = TimeToSecond(logs[i].substr(9, 8)) + 1;
		++arrViewer[Start];
		--arrViewer[End];
	}

	int PlayTime = TimeToSecond(play_time);
	int AdTime = TimeToSecond(adv_time);

	long long AccTime = 0;
	int Viewer[2] = { 0, 0 };
	long long Max = 0;
	int Idx = 0;
	for (int i = 1; i <= PlayTime; ++i)
	{
		if (0 < i - AdTime)
		{
			Viewer[1] += arrViewer[i - AdTime];
			AccTime -= Viewer[1];
		}

		Viewer[0] += arrViewer[i];
		AccTime += Viewer[0];

		if (Max < AccTime)
		{
			Max = AccTime;
			Idx = i < AdTime ? 0 : i - AdTime;
		}
	}

	string answer = "";
	answer += to_string(Idx / 3600 / 10);
	answer += to_string(Idx / 3600 % 10);
	answer += ":";
	answer += to_string(Idx % 3600 / 60 / 10);
	answer += to_string(Idx % 3600 / 60 % 10);
	answer += ":";
	answer += to_string(Idx % 60 / 10);
	answer += to_string(Idx % 60 % 10);

	return answer;
}