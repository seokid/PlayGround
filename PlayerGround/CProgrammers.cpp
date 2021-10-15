#include "CProgrammers.h"



//2021 KAKAO BLIND RECRUITMENT 광고 삽입
//가장 시청이 많은 시간대에 광고를 삽입해라
int TimeToSecond(string str)
{
	int Second = ((str[0] - '0') * 10 + str[1] - '0') * 3600
		+ ((str[3] - '0') * 10 + str[4] - '0') * 60
		+ (str[6] - '0') * 10 + str[7] - '0';
	return Second;
}

string SecondToTime(long long Second)
{

	string hour = to_string(Second / 3600 / 10);
	hour += to_string(Second / 3600 % 10);
	string minete = to_string(Second % 3600 / 60 / 10);
	minete += to_string(Second % 3600 / 60 % 10);
	string second = to_string(Second % 60 / 10);
	second += to_string(Second % 60 % 10);

	return hour + ":" + minete + ":" + second;
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



	return SecondToTime(Idx);
}