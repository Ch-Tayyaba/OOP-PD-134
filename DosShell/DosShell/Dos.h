#pragma once
#include<iostream>
#include"Tree.h"
#include"File.h"
#include"CurrentFile.h"

using namespace std;

class Dos
{
private:
	string Lower(string str);
	bool prompt = false;
public:
	Tree tree;
	string user = "Tayyaba";
	queue<File*> fileQueue;
	Dos(){}
	void print();
	void Run();
	bool Input();
};