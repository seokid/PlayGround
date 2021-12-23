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
		cout << IsPalindrome(0, (int)vec[i].size() - 1, vec[i], 0) << endl;
	}

}

//17610번
//양팔저울
//여러 개의 추를 이용하여 측정할 수 없는 무게의 개수를 출력하라

void DFSBalance(vector<int>& g, vector<int>& result, int Sum, int start)
{
	if (0 < Sum)
	{
		result[Sum] = 1;
	}
	
	for (size_t i = start + 1; i < g.size(); ++i)
	{
		DFSBalance(g, result, Sum + g[i], (int)i);
		DFSBalance(g, result, Sum - g[i], (int)i);
	}
}

void CBaekjoon::EqualArmBalance()
{
	int n;
	cin >> n;

	vector<int> g(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> g[i];
	}

	const int max = accumulate(g.begin(), g.end(), 0);

	vector<int> result(max + 1);

	DFSBalance(g, result, 0, -1);

	const int cnt = accumulate(result.begin(), result.end(), 0);	//체크된 총 개수

	cout << max - cnt << endl;
}


//17611번
//직각다각형
//직각다각형에서 가장 많이 교차하는 수직, 수평선분 중 가장 큰 값을 출력하라
void CBaekjoon::RightAnglePolygon()
{
	int n, x, y;
	cin >> n;

	vector<pair<int,int>> pos(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		pos[i] = make_pair(x, y);
	}

	pos.push_back(pos[0]);

	map<int, int> graphX;
	map<int, int> graphY;

	for (size_t i = 0; i < pos.size() - 1; ++i)
	{
		if (pos[i].first < pos[i + 1].first)
		{
			graphX[pos[i].first]++;
			graphX[pos[i + 1].first]--;
		}
		else if (pos[i].first > pos[i + 1].first)
		{
			graphX[pos[i + 1].first]++;
			graphX[pos[i].first]--;
		}

		if (pos[i].second < pos[i + 1].second)
		{
			graphY[pos[i].second]++;
			graphY[pos[i + 1].second]--;
		}
		else if (pos[i].second > pos[i + 1].second)
		{
			graphY[pos[i + 1].second]++;
			graphY[pos[i].second]--;
		}
	}

	int Max = INT32_MIN;
	int sum = 0;
	for (auto& pair : graphX)
	{
		sum += pair.second;
		Max = max(Max, sum);
	}

	sum = 0;
	for (auto& pair : graphY)
	{
		sum += pair.second;
		Max = max(Max, sum);
	}
	
	cout << Max << endl;
}


//17612번
//쇼핑몰
//손님이 계산대에서 빠져나가는 순서대로 1 * id1 + 2 * id2 ... N * idN의 합을 출력하라

struct tCustomer
{
	int id, work, counter;

	bool operator()(tCustomer Left, tCustomer Right)
	{
		if (Left.work == Right.work)
		{
			return Left.counter > Right.counter;
		}

		return Left.work > Right.work;
	}
};

bool ShoppingMall_compair(tCustomer Left, tCustomer Right)
{
	if (Left.work == Right.work)
	{
		return Left.counter > Right.counter;
	}

	return Left.work < Right.work;
}

void CBaekjoon::ShoppingMall()
{
	int n, k, id, w;
	long long answer = 0;
	cin >> n >> k;

	vector<tCustomer> ready;
	priority_queue<tCustomer, vector<tCustomer>, tCustomer> execute;
	vector<tCustomer> finish;


	for (int i = 0; i < n; ++i)
	{
		cin >> id >> w;
		ready.push_back({id, w, i});
	}

	int Idx = 0;

	for (; Idx < k && Idx < n; ++Idx)
	{
		execute.push(ready[Idx]);
	}

	while (n > finish.size())
	{
		tCustomer cust = execute.top(); execute.pop();
		finish.push_back(cust);
		if (n > Idx)
		{
			cust.id = ready[Idx].id;
			cust.work += ready[Idx++].work;
			execute.push(cust);
		}
	}

	sort(finish.begin(), finish.end(), ShoppingMall_compair);

	for (size_t i = 0; i < finish.size(); ++i)
	{
		answer += finish[i].id * (i + 1);
	}
	
	cout << answer << endl;

}
