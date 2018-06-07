#pragma once
#include<iostream>
#include<cstring>
//#define NDEBUG


using namespace std;



void StrtoArray(string &Input, int(&Output)[65]);

void De_StrtoArray(string &Input, int(&Output)[65]);

void DEC(int(&Input)[65], string &Output);

void DevisionToStr(string &Input, string &Output);

//≥ı º÷√ªª
void Dec_InitialRep_Transform(int(&Input)[65]);

void Dec_InitialKey_Select(int(&Input)[65]);

void LeftMove(int i);

void RightMove(int i);

void InitialKeys(string &Input);

void De_InitialKeys(string &Input);

void KeySelect(int n);

void SingleRound(int n);

void S_Rep();

void GetResult(string &Output);

void De_GetResult(string & Output);

void Transform(int n, string &Output);

void Extend();

void Reverse();

void Decryption(string &Input, string &Output);

int ReTransform(char A);

