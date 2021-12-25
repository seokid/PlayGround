// PlayerGround.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "global.h"
#include "func.h"
#include "CHackerRank.h"
#include "CProgrammers.h"
#include "CBaekjoon.h"

using namespace std;

void test();
void test2();
void test3();


int main()
{
	timeCheck(test);
	timeCheck(test2);
	timeCheck(test3);

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

void test()
{
	

}


void test2()
{
	
}


void test3()
{

}


