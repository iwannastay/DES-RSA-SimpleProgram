#include <iostream>	
#include "des.h"
#include "RSA.h"
#include <fstream>

#define FILE_LEN 500

int main()
{

	string str = "students",//秘钥
		Input = "i am a student, you are a pig",//明文
		Output, //密文
		Output2;//解密

	char key[9] = { 0 };
	char file[FILE_LEN+1] = { 0 };

	fstream keys, Msgs;
	keys.open("key.txt");
	if (keys)
	{
		keys.read(key, 8);
		str = key;
	}

	Msgs.open("file.txt");
	if (Msgs)
	{
		Msgs.read(file, FILE_LEN);
		Input = file;
	}
	cout << "DES加密解密\n" << "明文：" << Input.c_str() << "\n8位秘钥：" << str.c_str() << endl;

	InitialKeys(str);

	DevisionToStr(Input, Output);

	cout << "密文:" << Output.c_str() << endl;

	De_InitialKeys(str);

	Decryption(Output, Output2);

	cout << "解密:" << Output2.c_str() << endl;

	int Msg = 40;
	int P = 13;
	int Q = 41;
	int N;
	int L;
	int E;
	int D;

	//int Msg = 3;
	//int P = 17;
	//int Q = 11;
	//int N = 187;
	//int L = 160;
	//int E = 7;
	//int D = 23;

	//int Msg = 3;
	//int P = 3;
	//int Q = 11;
	//int N = 33;
	//int L = 20;
	//int E = 3;
	//int D = 7;

	cout << "\nRSA加密解密" << "\n明文：" << Msg << "\n选择质数:" << 13 << " " << 41 << endl;

	if (GetKeys(P, Q, &E, &D, &N))
	{
		cout << "生成公钥（N,E)：(" << N << "," << E << ")" << endl;
		cout << "生成密钥（N,D)：(" << N << "," << D << ")" << endl;

		int Mid = RSA_Encryption(Msg, E, N);

		cout << "密文：" << Mid << endl;

		int Res = RSA_Encryption(Mid, E, N);

		cout << "解密：" << Res << endl;
	}
	else
		cout << "Fail to Make Keys";
	return 0;
}

