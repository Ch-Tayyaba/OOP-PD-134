#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<iostream>
#include<ctime>
#include<time.h>
#include<string>
#include"CurrentFile.h"

using namespace std;

class File
{
public:
	string name;
	time_t creationTime;
	string path;
	string Time;
	string extension;
	bool hidden;
	list<list<char>> data;
	int size;
	CurrentFile* edit;
	File(string _Name = "Null", string _Path = "", time_t _Creation_Time = time(0), bool _Hiddden = false, string _Extension = ".txt", int _size = -1)
	{
		name = _Name;
		extension = _Extension;
		path = _Path;
		creationTime = _Creation_Time;
		Time = ctime(&creationTime);
		ConvertTime(Time);
		hidden = _Hiddden;
		size = _size;
		CreationOfFile();
	}
	void Print();
	void ConvertTime(string& Time);
	void CreationOfFile();
};