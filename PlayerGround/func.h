#pragma once

#include "global.h"

void timeCheck(void(*func)(), const string& funcName)
{
	chrono::system_clock::time_point start = chrono::system_clock::now();
	func();
	chrono::duration<double> sec = chrono::system_clock::now() - start;
	cout << funcName << " �ɸ��ð� : " << sec.count() << endl;
}
