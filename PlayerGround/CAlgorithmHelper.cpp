#include "CAlgorithmHelper.h"

int CAlgorithmHelper::Combination_Recursion(int n, int r)
{
	if (n == r || r == 0)
		return 1;

	return Combination_Recursion(n - 1, r - 1) + Combination_Recursion(n - 1, r);	//조합 공식 n-1Cr-1 + n-1Cr == nCr
}
