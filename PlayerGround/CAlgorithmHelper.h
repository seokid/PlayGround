#pragma once

#include <vector>



class CAlgorithmHelper
{
public:
	template<typename T1, typename T2>
	static int BinarySearch(const T1 BeginIter, const T1 EndIter, const T2& Find);

	static int Combination_Recursion(int n, int r);
};

template<typename T1, typename T2>
int CAlgorithmHelper::BinarySearch(const T1 BeginIter, const T1 EndIter, const T2& Find)
{
	int begin = 0;
	int end = EndIter - BeginIter;
	int mid;

	while (begin <= end)
	{
		mid = (begin + end) / 2;

		if (Find == BeginIter[mid])
		{
			return mid;
		}
		else if (Find > BeginIter[mid])
		{
			begin = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}
	return -1;
}