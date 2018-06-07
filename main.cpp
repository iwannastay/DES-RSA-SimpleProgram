#include <iostream>	
#include "des.h"
#include "RSA.h"
#include <fstream>

#define FILE_LEN 500

int main()
{

	string str = "students",//��Կ
		Input = "i am a student, you are a pig",//����
		Output, //����
		Output2;//����

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
	cout << "DES���ܽ���\n" << "���ģ�" << Input.c_str() << "\n8λ��Կ��" << str.c_str() << endl;

	InitialKeys(str);

	DevisionToStr(Input, Output);

	cout << "����:" << Output.c_str() << endl;

	De_InitialKeys(str);

	Decryption(Output, Output2);

	cout << "����:" << Output2.c_str() << endl;

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

	cout << "\nRSA���ܽ���" << "\n���ģ�" << Msg << "\nѡ������:" << 13 << " " << 41 << endl;

	if (GetKeys(P, Q, &E, &D, &N))
	{
		cout << "���ɹ�Կ��N,E)��(" << N << "," << E << ")" << endl;
		cout << "������Կ��N,D)��(" << N << "," << D << ")" << endl;

		int Mid = RSA_Encryption(Msg, E, N);

		cout << "���ģ�" << Mid << endl;

		int Res = RSA_Encryption(Mid, E, N);

		cout << "���ܣ�" << Res << endl;
	}
	else
		cout << "Fail to Make Keys";
	return 0;
}

