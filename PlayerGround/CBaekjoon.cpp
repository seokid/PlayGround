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
		cout << IsPalindrome(0, (int)vec[i].size() - 1, vec[i], 0) << endl;
	}

}

//17610��
//��������
//���� ���� �߸� �̿��Ͽ� ������ �� ���� ������ ������ ����϶�

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

	const int cnt = accumulate(result.begin(), result.end(), 0);	//üũ�� �� ����

	cout << max - cnt << endl;
}


//17611��
//�����ٰ���
//�����ٰ������� ���� ���� �����ϴ� ����, ���򼱺� �� ���� ū ���� ����϶�
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


//17612��
//���θ�
//�մ��� ���뿡�� ���������� ������� 1 * id1 + 2 * id2 ... N * idN�� ���� ����϶�

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
