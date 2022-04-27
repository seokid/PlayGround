#include "CProgrammers.h"

#define INF 1e8

int answer;

//2021 KAKAO BLIND RECRUITMENT 합승 택시 요금
//두 사람이 모두 귀가하는 데 소요되는 예상 최저 택시요금 반환, 합승 가능
//Floyd Warshall 알고리즘을 사용하여 모든 노드의 최단거리를 구하여 최소요금 계산
int CProgrammers::carPool(int n, int s, int a, int b, vector<vector<int>> fares) {
	answer = (int)INF;
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


//2021 KAKAO BLIND RECRUITMENT 광고 삽입
//가장 시청이 많은 시간대에 광고를 삽입해라
int TimeToSecond(string str)
{
	int Second = ((str[0] - '0') * 10 + str[1] - '0') * 3600
		+ ((str[3] - '0') * 10 + str[4] - '0') * 60
		+ (str[6] - '0') * 10 + str[7] - '0';
	return Second;
}

int arrViewer[360001];

string CProgrammers::videoADInsert(string play_time, string adv_time, vector<string> logs) {

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

	string strAnswer = "";
	strAnswer += to_string(Idx / 3600 / 10);
	strAnswer += to_string(Idx / 3600 % 10);
	strAnswer += ":";
	strAnswer += to_string(Idx % 3600 / 60 / 10);
	strAnswer += to_string(Idx % 3600 / 60 % 10);
	strAnswer += ":";
	strAnswer += to_string(Idx % 60 / 10);
	strAnswer += to_string(Idx % 60 % 10);

	return strAnswer;
}



//2021 KAKAO BLIND RECRUITMENT 카드 짝 맞추기
//커서를 이동시켜서 카드 짝 맞추는 최소 비용 계산
//DFS + 다익스트라
struct tCard
{
	int cost;
	pair<int, int> pos;

	tCard() {}
	tCard(int _cost, pair<int, int> _pos) : cost(_cost), pos(_pos) {}

};

bool operator < (const tCard& Left, const tCard& Right)
{
	return Left.cost > Right.cost;
}

int cardMatch_dijkstra(const pair<int, int>& start, const pair<int, int>& dest, const vector<vector<int>>& board)
{
	vector<vector<int>> cost(4);
	for (int i = 0; i < 4; ++i)
	{
		cost[i].resize(4);
		fill(cost[i].begin(), cost[i].end(), INF);
	}

	priority_queue<tCard> pq;

	pq.push(tCard(0, start));
	cost[start.first][start.second] = 0;

	int arrDirX[4] = { 0,0,-1,1 };
	int arrDirY[4] = { -1,1,0,0 };

	while (!pq.empty())
	{
		pair<int, int> cur = pq.top().pos;
		int curCost = pq.top().cost;
		pq.pop();

		if (cur == dest) 
			return curCost;

		for (int j = 0; j < 8; ++j)
		{
			pair<int, int> next = { cur.first , cur.second };

			while (true)
			{
				if ((-1 == arrDirY[j % 4] && 0 == next.first) || (1 == arrDirY[j % 4] && 3 == next.first))
					break;

				if ((-1 == arrDirX[j % 4] && 0 == next.second) || (1 == arrDirX[j % 4] && 3 == next.second))
					break;

				next.first += arrDirY[j % 4];
				next.second += arrDirX[j % 4];

				if (j < 4 || 0 != board[next.first][next.second])
					break;
			}

			if (cost[next.first][next.second] > curCost + 1)
			{
				cost[next.first][next.second] = curCost + 1;
				pq.push(tCard(curCost + 1, next));
			}
		}
	}
	return 0;
}

bool cardMatch_IsFinish(const vector<vector<int>>& board)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (0 != board[i][j])
				return false;
	return true;
}

void cardMatch_DFS(const pair<int, int>& cursor, int total, vector<vector<int>>& board)
{
	if (answer < total)
		return;

	if (cardMatch_IsFinish(board))
		answer = min(answer, total);

	vector<pair<int, int>> dest;

	for (int i = 1; i <= 6; ++i)
	{
		dest.clear();

		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				if (i == board[y][x])
				{
					dest.push_back({ y,x });
				}
			}
		}

		if (dest.empty())
			continue;

		vector<vector<int>> cost;
		pair<int, int> count = { 2,2 };
		count.first += cardMatch_dijkstra(cursor, dest[0], board) + cardMatch_dijkstra(dest[0], dest[1], board);
		count.second += cardMatch_dijkstra(cursor, dest[1], board) + cardMatch_dijkstra(dest[1], dest[0], board);

		board[dest[0].first][dest[0].second] = 0;
		board[dest[1].first][dest[1].second] = 0;

		cardMatch_DFS(dest[1], total + count.first, board);
		cardMatch_DFS(dest[0], total + count.second, board);

		board[dest[0].first][dest[0].second] = i;
		board[dest[1].first][dest[1].second] = i;
	}
}

int CProgrammers::cardMatch(vector<vector<int>> board, int r, int c) {
	answer = INT32_MAX;

	pair<int, int> cursor(r, c);

	cardMatch_DFS(cursor, 0, board);

	return answer;
}




//2019 KAKAO BLIND RECRUITMENT 매칭점수
//문자열 파싱

void matchPoint_Parsing(const string & page, const string & startWord, const string & endWord, vector<string>& result)
{
	size_t startIdx = page.find(startWord);
	size_t endIdx;

	while (string::npos != startIdx)
	{
		startIdx += startWord.size();
		endIdx = page.find(endWord, startIdx) - startIdx;
		result.push_back(page.substr(startIdx, endIdx));
		startIdx = page.find(startWord, startIdx + endIdx);
	}
}

void matchPoint_Split(const string& str, vector<string>& result)
{
	string tmp = "";

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!('a' <= str[i] && 'z' >= str[i]))
		{
			if (!tmp.empty())
			{
				result.push_back(tmp);
				tmp = "";
			}
				
			continue;
		}
		tmp += str[i];
	}

	if (!tmp.empty())
		result.push_back(tmp);
}


int CProgrammers::matchPoint(string word, vector<string> pages)
{
	int answer = 0;

	transform(word.begin(), word.end(), word.begin(), ::tolower);

	unordered_map<string, int> map;
	vector<vector<string>> links;
	vector<double> basicScore;

	for (size_t i = 0; i < pages.size(); ++i)
	{
		transform(pages[i].begin(), pages[i].end(), pages[i].begin(), ::tolower);

		vector<string> result;
		matchPoint_Parsing(pages[i], "<meta property=\"og:url\" content=\"https://", "\"/>", result);

		map.insert({ result[0], i });

		matchPoint_Parsing(pages[i], "<body>", "</body>", result);

		string body = result[1];

		result.clear();
		matchPoint_Split(body, result);

		int basicPoint = 0;

		for (size_t j = 0; j < result.size(); ++j)
		{
			if (word == result[j])
				++basicPoint;
		}

		basicScore.push_back((double)basicPoint);

		result.clear();
		matchPoint_Parsing(body, "<a href=\"https://", "\">", result);

		links.push_back(result);
	}

	vector<double> linkScore(basicScore);
	for (size_t i = 0; i < links.size(); ++i)
	{
		for (const auto& link : links[i])
		{
			auto iter = map.find(link);
			if (iter != map.end())
			{
				linkScore[iter->second] += basicScore[i] / (double)links[i].size();
			}
		}
	}

	double maxScore = 0.f;
	for (size_t i = 0; i < linkScore.size(); ++i)
	{
		if (maxScore < linkScore[i])
		{
			answer = i;
			maxScore = linkScore[i];
		}
	}

	return answer;

}


void brian_split(string& str, vector<string>& result)
{
	string tmp = "";

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (' ' == str[i])
			continue;



		tmp += str[i];
	}

	if (!tmp.empty())
		result.push_back(tmp);
}

string CProgrammers::brianConsider(string str)
{
	vector<string> result;

	brian_split(str, result);

	for (string st : result)
	{
		cout << st << endl;
	}
	return "";
}
