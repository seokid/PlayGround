// PlayerGround.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "global.h"
#include "func.h"
#include "CHackerRank.h"
#include "CProgrammers.h"
#include "CBaekjoon.h"
#include "CFileAlter.h"
#include "CAlgorithmHelper.h"

using namespace std;

void test();
void test2();
void test3();


int main()
{
	/*timeCheck(test, "test");
	timeCheck(test2, "test2");*/
	timeCheck(test3, "test3");

	return 0;
}


enum class EElementSkill : int32_t
{

	//Fire
	C3000 = 0x03000000,
	C2100 = 0x02010000,
	C2010 = 0x02000100,
	C2001 = 0x02000001,

	//Water
	C1200 = 0x01020001,
	C0300 = 0x00030000,
	C0210 = 0x00020100,
	C0201 = 0x00020001,

	//Earth
	C1020 = 0x01000200,
	C0120 = 0x00010200,
	C0030 = 0x00000300,
	C0021 = 0x00000201,

	//Wind
	C1002 = 0x01000002,
	C0102 = 0x00010002,
	C0012 = 0x00000102,
	C0003 = 0x00000003,

	//Mix
	C1110 = 0x01010100,
	C1101 = 0x01010001,
	C1011 = 0x01000101,
	C0111 = 0x00010101,

};


union ElementComb
{
	struct
	{
		char Wind;
		char Earth;
		char Water;
		char Fire;
	};

	int Key;
};


void ElementToBinary(EElementSkill Skill)
{
	cout << (int32_t)Skill << endl;
}

int count_bit(unsigned int ux) {
	unsigned int cnt = ux - ((ux >> 1) & 033333333333) - ((ux >> 2) & 011111111111);
	return ((cnt + (cnt >> 3)) & 030707070707) % 63;
}


void test()
{
	
	CProgrammers::matchPoint("Muzi", { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>" });
	
}


#include <set>


bool cmp(pair<string, int> L, pair<string, int> R)
{
	return L.second > R.second;
}

struct tHash
{
	string genre;
	int play;

	bool operator < (const tHash& other) const
	{
		if (genre == other.genre)
			return play < other.play;
		return genre < other.genre;
	}

	bool operator==(const tHash &other) const
	{
		return genre == other.genre && play == other.play;
	}
};

namespace std {

	template <>
	struct hash<tHash>
	{
		std::size_t operator()(const tHash& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return ((hash<string>()(k.genre)
				^ (hash<int>()(k.play) << 1)) >> 1);
		}
	};
}
//
//vector<int> solution(vector<string> genres, vector<int> plays) {
//	vector<int> answer;
//
//	unordered_map<string, int> genreId;
//	vector<string> type = genres;
//	type.erase(unique(type.begin(), type.end()), type.end());
//
//	for (size_t i = 0; i < type.size(); ++i)
//	{
//		genreId[type[i]] = i;
//	}
//
//	vector<tHash> total(type.size());
//	unordered_map<string, vector<pair<int, int>>> genrePlay;
//
//	for (size_t i = 0; i < plays.size(); ++i)
//	{
//		genrePlay[genres[i]].push_back({ plays[i], i});
//		total[genreId[genres[i]]].genre = genreId[genres[i]];
//		total[genreId[genres[i]]].play += plays[i];
//	}
//
//	sort(total.begin(), total.end());
//
//	for (size_t i = 0; i < total.size(); ++i)
//	{
//		sort(genrePlay[total[i].genre].begin(), genrePlay[total[i].genre].end(), greater<>());
//		int cnt = min(2, (int)genrePlay[total[i].genre].size());
//		for (int j = 0; j < cnt; ++j)
//		{
//			answer.push_back(genrePlay[total[i].genre][j].second);
//		}
//	}
//
//	
//	
//	
//
//	
//
//
//	
//
//	return answer;
//}

vector<int> solution(vector<string> vec) {


	set<int> st;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		int num = stoi(vec[i].substr(2));
		if ('I' == vec[i][0])
		{
			st.insert(num);
		}
		else if (st.empty())
			continue;

		else if ('D' == vec[i][0] && 1 == num)
		{
			st.erase(--st.end());
		}
		else
		{
			st.erase(st.begin());
		}
	}

	if (st.empty())
		return { 0, 0 };

	
	return { *(--st.end()), *st.begin() };
}

void test2()
{

}




unordered_map<string, int> g_cost;
vector<int> g_money;
int g_answer;



int findCost(vector<string> path)
{
	string key = "";
	for (size_t i = 0; i < path.size(); ++i)
	{
		key += path[i];
	}

	if (g_cost.count(key))
	{
		return g_cost[key];
	}

	int Idx = stoi(path.back());
	path.pop_back();
	return g_cost[key] = findCost(path) + g_money[Idx];
}

void dfs(vector<string> path, int cur)
{
	if (g_money.size() <= stoi(path.back()) + 2)
	{
		//answer = max(answer, findCost(path));
		int cost = findCost(path);
		if (g_answer < cost)
		{
			g_answer = cost;
			for (size_t i = 0; i < path.size(); ++i)
			{
				cout << path[i] << endl;
			}
		}
		return;
	}

	for (int i = 2; i < 4; ++i)
	{
		if (cur + i < g_money.size())
		{
			path.push_back(to_string(cur + i));
			dfs(path, cur + i);
			path.pop_back();
		}
		
	}
}

int solution4(vector<int> money) {


	g_money = money;


	for (size_t i = 0; i < 2; ++i)
	{
		g_cost.insert({ to_string(i), g_money[i] });
		vector<string> path = { to_string(i) };
		dfs(path, i);
	}

	return g_answer;
}

long maximumSum(vector<long> a, long m) {

	long answer = 0l;
	long Sum = 0l;

	set<long> st;
	for (size_t i = 0; i < a.size(); ++i)
	{
		Sum = (Sum + a[i]) % m;
		answer = max(answer, Sum);
		set<long>::iterator iter = st.lower_bound(Sum + 1);

		if (st.end() != iter)
		{
			answer = max(answer, (Sum - *iter + m) % m);
		}
		st.insert(Sum);
	}

	return answer;
}

int solution3(int bridge_length, int weight, vector<int> vec) {

	int Time = 1;
	int curWeight = 0;

	queue<pair<int, int>> bridge;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (!bridge.empty() && weight >= curWeight + vec[i])
		{
			Time = bridge.back().second + 1;
			curWeight += vec[i];
			bridge.push({ vec[i], Time });

		}
		else
		{
			while (weight < curWeight + vec[i])
			{
				Time = bridge.front().second;
				weight -= bridge.front().first;
				bridge.pop();
			}

			Time += bridge_length;
			curWeight += vec[i];
			bridge.push({ vec[i], Time });
		}
	}

	return Time;
}

void test3()
{
	vector<int> vec = { 7, 4, 5, 6 };
	solution3(2, 10, vec);
	
	//1802192837
	//maximumSum(vec, 7);
}


