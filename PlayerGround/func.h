#pragma once

#include <chrono>
#include <iostream>

using namespace std;

void timeCheck(void(*func)())
{
	chrono::system_clock::time_point start = chrono::system_clock::now();
	func();
	chrono::duration<double> sec = chrono::system_clock::now() - start;
	cout << "걸린시간 : " << sec.count() << endl;
}
