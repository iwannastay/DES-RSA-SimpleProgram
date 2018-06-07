#pragma once
#include <math.h>

int RSA_Encryption(int _Msg, int E, int N);

int RSA_Decryption(int _Msg, int D, int N);

bool GetKeys(int P, int Q, int *E, int *D, int *N);

int S(int B, int D, int N);
