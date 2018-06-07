#include "RSA.h"
#include <math.h>

int RSA_Encryption(int _Msg, int E, int N)
{

	return S(_Msg, E, N);
}

int RSA_Decryption(int _Msg, int D, int N)
{
	return S(_Msg, D, N);
}

bool GetKeys(int P, int Q, int *E, int *D, int *N)
{
	*N = P*Q;
	int L = (P - 1)* (Q - 1);
	int n = 1;
	while (n) {
		int Temp = (n++)*L + 1;
		int K = sqrt(Temp);
		for (int i = 2; i <= K; i++)
		{
			if (Temp % i == 0)
			{
				*E = Temp / i;
				*D = i;
				n = 0;
				break;
			}
		}
		if (n > 5) return false;
	}

	return true;
}

int S(int B, int D, int N)
{
	if (D > 3)
	{
		int X = D / 3, Y = D % 3;

		int S1 = S((int)pow(B, 3) % N, X, N);
		int S2 = S(B, Y, N);

		return (S1*S2) % N;
	}
	else
		return((int)pow(B, D) % N);
}
