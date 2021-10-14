// PlayerGround.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "func.h"
#include "CHackerRank.h"


using namespace std;

void test();
void test2();


int main()
{
	timeCheck(test);
	timeCheck(test2);

	return 0;
}


void test()
{
	vector<vector<int>> vec = {{2, 3},
		{- 1, - 1},
		{- 1, - 1},};
	vector<int> query = {1, 1};
	
	CHackerRank::swapNodes(vec, query);
}

void test2()
{
	//CHackerRank::reverseShuffleMerge("");
}
