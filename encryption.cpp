#include "des.h"

int Encry = 1;


int Add;

int Empty[65] = { 0 };
int Part[2][28] = { 0 };
int MoveKey[16] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

int De_MoveKey[16] = {
	0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

int SelectBoard[49] = { 0,
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
};

int R_Extend[49] = { 0,
	32,1,2,3,4,5,
	4,5,6,7,8,9,
	8,9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32,1
};
int Extended_R[49] = { 0 };

int LR[2][33] = { 0 };

int InitialRep[65] = { 0,
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17, 9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
};

int De_InitialRep[65] = { 0,
40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,33,1,41, 9,49,17,57,25
};

int InitialKey[56] = {
	57,49,41,33,25,17,9,1,
	58,50,42,34,26,18,10,2,
	59,51,43,35,27,19,11,3,
	60,52,44,36,63,55,47,39,
	31,23,15,7,62,54,46,38,
	30,22,14,6,61,53,45,37,
	29,21,13,5,28,20,12,4
};

int Keys[16][49] = { 0 };

int S[8][4][16] = {
	{ {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
	 {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
	 {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
	 {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	},
	{ {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
	 {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
	 {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
	 {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	},
	{ {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
	{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
	{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
	{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
	},
	{ {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
	{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
	{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
	{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	},
	{ {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
	{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
	{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
	{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
	},
	{ {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
	{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
	{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
	{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	},
	{ {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
	{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
	{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
	{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	},
	{ {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
	{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
	{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
	{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
};

int S_Replace[33] = { 0,
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
};


//test
//int main()
//{
//	string str("FUCK YOU,bitch?"), str2;
//	DevisionToStr(str, str2);
//	return 0;
//}

void DevisionToStr(string &Input, string &Output)
{
	string Temp;
	int Len = Input.length();
	int Loop = Len / 8 ;
	int Tail = Len % 8;
	if (Tail)
	{
		Add = 8 - Tail;
		Loop++;
	}
	else Add = 0;
	for (int i = 0; i < Loop; i++)
	{
		Temp = "";
		if (Tail&&(Loop - i) == 1)
		{
			string New = Input.substr(i * 8, Tail);
			New.append(Add, '*');
			StrtoArray(New, Empty);
		}
		else
			StrtoArray(Input.substr(i * 8, 8), Empty);  
		DEC(Empty, Temp);
		Output += Temp;
	}
	//int len = Output.length();
	//len -= Add * 2;
	//Output.erase(len);
}

void Decryption(string &Input, string &Output)
{
	Encry = 0;
	string Temp;
	int Len = Input.length();
	int Loop = Len / 16 ;
	//int Tail = Len % 16;
	//if (Tail)
	//{
	//	Add = 16 - Tail;
	//	Loop++;
	//}
	//else Add = 0;
	for (int i = 0; i < Loop; i++)
	{
		Temp = "";
		/*if (Tail&&(Loop - i) == 1)
		{
			string New = Input.substr(i * 16, Tail);
			New.append(Add, '*');
			De_StrtoArray(New, Empty);
		}
		else*/
			De_StrtoArray(Input.substr(i * 16, 16), Empty);
		DEC(Empty, Temp);
		Output += Temp;
	}
	int len = Output.length();
	len -= Add;
	Output.erase(len);
}

void DEC(int(&Input)[65], string &Output)
{
	//初始置换
	Dec_InitialRep_Transform(Input);  

	//将数据块分为L0 和R0
	for (int i = 1; i < 33; i++)
	{
		LR[0][i] = Input[i];
		LR[1][i] = Input[i + 32];  
	}

	//对L0 R0进行16次轮变换
	for (int i = 0; i < 16; i++)
		SingleRound(i);

	////置换L16 和 R16
	//for (int i = 1, K = 0; i < 33; i++)
	//{
	//	K = LR[0][i];
	//	LR[0][i] = LR[1][i];
	//	LR[1][i] = K;
	//}

	//逆初始置换 & 置换 L16、R16
	int Ves[65] = { 0 };
	for (int i = 1; i < 33; i++)
	{
		Ves[i] = LR[1][i];
		Ves[i + 32] = LR[0][i];
	}
	for (int i = 1; i < 65; i++)
		Input[i] = Ves[De_InitialRep[i]]; 

	if(Encry ==1)
	GetResult(Output); 
	else De_GetResult(Output);
}

//Test
//int main()
//{
//	int a[65] = { 0 };
//	a[58] = 2;
//	a[62] = 4;
//	a[7] = 1;
//	Dec_InitialRep_Transform(a);
//	return 0;
//}

void Dec_InitialRep_Transform(int(&Input)[65])
{
	int Temp[65] = { 0 };
	for (int i = 1; i < 65; i++)
		Temp[i] = Input[i];
	for (int i = 1; i < 65; i++)
		Input[i] = Temp[InitialRep[i]];
}

void SingleRound(int n)
{
	Extend();

	for (int i = 1; i < 49; i++)
		Extended_R[i] ^= Keys[n][i];

	S_Rep();
}

void Extend()
{
	for (int i = 1; i < 49; i++)
		Extended_R[i] = LR[1][R_Extend[i]];
}
void Reverse()
{
}


void S_Rep()
{
	int Ves[33] = { 0 };
	for (int i = 1; i < 33; i++)
		Ves[i] = LR[1][i];

	int Old, New, Row, Col;
	for (int i = 0; i < 8; i++)
	{
		Old = i * 6 + 1;
		New = i * 4 + 1;
		Row = (Extended_R[Old] << 1) + Extended_R[Old + 5];
		Col = (Extended_R[Old + 1] << 3) + (Extended_R[Old + 2] << 2)
			+ (Extended_R[Old + 3] << 1) + (Extended_R[Old + 4]);
		int Res = S[i][Row][Col];
		for (int j = 3; j >= 0; j--)
		{
			LR[1][New + j] = Res % 2;
			Res /= 2;
		}
	}

	
	for (int i = 1; i < 33; i++)
		LR[1][i] = Ves[S_Replace[i]];

	for (int i = 1; i < 33; i++)
	{
		LR[1][i] ^= LR[0][i];
		LR[0][i] = Ves[i];
	}

}

void GetResult(string & Output)
{
	string Temp;
	int A, C;
	for (int i = 0; i < 16; i++)
	{
		A = 3;
		C = 0;
		for (int j = 1; j < 5; j++, A--)
		{
			C += Empty[i * 4 + j] << A;
		}
		Transform(C, Temp);
	}
	Output += Temp;
}

void De_GetResult(string & Output)
{
	char W;
	string Temp;
	int A, C;
	for (int i = 0; i < 8; i++)
	{
		A = 7;
		C = 0;
		for (int j = 1; j < 9; j++, A--)
		{
			C += Empty[i * 8 + j] << A;
		}
		W = C;
		Temp += W;
	}
	Output += Temp;
}

void Transform(int n, string &Output)
{
	char A;
	switch (n)
	{
	case 0:
		A = '0'; break;
	case 1:
		A = '1'; break;
	case 2:
		A = '2'; break;
	case 3:
		A = '3'; break;
	case 4:
		A = '4'; break;
	case 5:
		A = '5'; break;
	case 6:
		A = '6'; break;
	case 7:
		A = '7'; break;
	case 8:
		A = '8'; break;
	case 9:
		A = '9'; break;
	case 10:
		A = 'A'; break;
	case 11:
		A = 'B'; break;
	case 12:
		A = 'C'; break;
	case 13:
		A = 'D'; break;
	case 14:
		A = 'E'; break;
	case 15:
		A = 'F'; break;
	default:
		A = '?';
	}
	Output += A;
} 

int ReTransform(char A)
{
	int n;
	switch (A)
	{
	case '0':
		n = 0; break;
	case '1':
		n = 1; break;
	case '2':
		n = 2; break;
	case '3':
		n = 3; break;
	case '4':
		n = 4; break;
	case '5':
		n = 5; break;
	case '6':
		n = 6; break;
	case '7':
		n = 7; break;
	case '8':
		n = 8; break;
	case '9':
		n = 9; break;
	case 'A':
		n = 10; break;
	case 'B':
		n = 11; break;
	case 'C':
		n = 12; break;
	case 'D':
		n = 13; break;
	case 'E':
		n = 14; break;
	case 'F':
		n = 15; break;
	default:
		n = 0; break;
	}
	return n;
}

void InitialKeys(string &Input)
{
	int Temp[65] = { 0 };
	StrtoArray(Input, Temp);
	Dec_InitialKey_Select(Temp);
	for (int i = 0; i < 16; i++)
	{
		LeftMove(i);
		KeySelect(i);
	}
}

void De_InitialKeys(string &Input)
{
	int Temp[65] = { 0 };
	StrtoArray(Input, Temp);
	Dec_InitialKey_Select(Temp);
	for (int i = 0; i < 16; i++)
	{
		RightMove(i);
		KeySelect(15-i);
	}
}

//Test
//int main()
//{
//	string str("FUCK YOU");
//	int Array[65] = { 0 };
//	StrtoArray(str, Array);
//	return 0;
//}
void StrtoArray(string &Input, int(&Output)[65])
{
	memset(Empty, 0, 65 * sizeof(int));
	_ASSERT(Input.length() == 8);
	int Temp, N;
	for (int i = 1, j = 0; i < 9; i++, j = 0)
	{
		Temp = Input[i - 1];
		do {
			N = Temp % 2;
			Temp /= 2;
			Output[i * 8 - j] = N;
			j++;
		} while (Temp != 0);
	}
}

void De_StrtoArray(string &Input, int(&Output)[65])
{
	memset(Empty, 0, 65 * sizeof(int));
	_ASSERT(Input.length() == 16);
	int Temp, N;
	for (int i = 1, j = 0; i < 17; i++, j = 0)
	{
		Temp = ReTransform(Input[i - 1]);
		do {
			N = Temp % 2;
			Temp /= 2;
			Output[i * 4 - j] = N;
			j++;
		} while (Temp != 0);
	}
}

void Dec_InitialKey_Select(int(&Input)[65])
{
	memset(Empty, 0, 65 * sizeof(int));
	for (int i = 0; i < 56; i++)
		Empty[i] = Input[InitialKey[i]];
	for (int j = 0; j < 28; j++)
	{
		Part[0][j] = Empty[j];
		Part[1][j] = Empty[j + 28];
	}
}

void LeftMove(int i)
{
	int Temp[2];
	if (MoveKey[i] == 1)
	{
		for (int k = 0; k < 2; k++)
		{
			Temp[0] = Part[k][0];
			for (int i = 0; i < 27; i++)
				Part[k][i] = Part[k][i + 1];
			Part[k][27] = Temp[0];
		}
	}
	else
	{
		for (int k = 0; k < 2; k++)
		{
			Temp[0] = Part[k][0];
			Temp[1] = Part[k][1];
			for (int i = 0; i < 26; i++)
				Part[k][i] = Part[k][i + 2];
			Part[k][26] = Temp[0];
			Part[k][27] = Temp[1];
		}
	}

}

void RightMove(int i)
{
	int Temp[2];
	if (De_MoveKey[i] == 1)
	{
		for (int k = 0; k < 2; k++)
		{
			Temp[0] = Part[k][27];
			for (int i = 27; i >0; i--)
				Part[k][i] = Part[k][i - 1];
			Part[k][0] = Temp[0];
		}
	}
	else if (De_MoveKey[i] == 2)
	{
		for (int k = 0; k < 2; k++)
		{
			Temp[0] = Part[k][26];
			Temp[1] = Part[k][27];
			for (int i = 27; i >1; i--)
				Part[k][i] = Part[k][i - 2];
			Part[k][0] = Temp[0];
			Part[k][1] = Temp[1];
		}
	}

}

void KeySelect(int n)
{
	memset(Empty, 0, 65 * sizeof(int));
	for (int i = 0; i < 28; i++)
	{
		Empty[i + 1] = Part[0][i];
		Empty[i + 29] = Part[1][i];
	}

	for (int j = 1; j < 49; j++)
		Keys[n][j] = Empty[SelectBoard[j]];
}




//void Dec_InitialRep_Transform(int(&Input)[65])
//{
//	int Pos = 1;
//	int Temp = Input[Pos];
//	do{
//	Input[Pos] = Input[InitialRep[Pos]];
//	Pos = InitialRep[Pos];
//	} while (InitialRep[Pos] != 1);
//	Input[Pos] = Temp;
//}