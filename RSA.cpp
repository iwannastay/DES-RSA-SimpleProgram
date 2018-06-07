#include "RSA.h"

int RSA_Encryption(int _Msg, int E, int N)
{
	int M = _Msg^E;
	return M % N;
}

int RSA_Decryption(int _Msg, int D, int N)
{
	int M = _Msg^D;
	return M % N;
}

bool GetKeys(int P, int Q, int *E, int *D,int *N)
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
				*E = i;
				*D = Temp / i;
				n = 0;
				break;
			}
		}
		if (n > 5) return false;
	}

	return true;
}
