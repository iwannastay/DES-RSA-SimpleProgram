#include <iostream>	
#include "des.h"
#include "RSA.h"
#include <fstream>
#include <list>

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

	int Msg,Mid,Res;//明文，密文，解密
	int P = 33;
	int Q = 41;
	int N,L,E,D;
	list<int> MidList;

	
	Input = "112233445566";

	cout << "\nRSA加密解密" << "\n明文：" << Input.c_str() << "\n选择质数:" << P << " " << Q << endl;

	if (GetKeys(P, Q, &E, &D, &N))
	{
		cout << "生成公钥（N,E)：(" << N << "," << E << ")" << endl;
		cout << "生成密钥（N,D)：(" << N << "," << D << ")" << endl;
		
		cout << "密文：";

		auto iter = Input.begin();
		while (iter != Input.end())
		{
			Msg = (*iter) - 48;
			Mid = RSA_Encryption(Msg, E, N);
			MidList.push_back(Mid);
			cout << Mid << ",";
			iter++;
		}

		cout << "\n解密：";

		auto _iter = MidList.begin();
		while (_iter != MidList.end())
		{
			Res = RSA_Decryption((*_iter), D, N);
			cout << Res;
			_iter++;
		}
		
	}
	else
		cout << "Fail to Make Keys";
	return 0;
}


