#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <list>
#include<time.h>
#include <ctime>
#include "File.h"

using namespace std;

class Folder
{
public:
	string name;
	list<Folder*> folders;
	list<File*> files;
	Folder* parent;
	CurrentFile* CF;
	time_t creationTime;
	string Time;
	string owner;
	string path;
	bool hidden;

	Folder(string n = "", string p = "", Folder* Parent = nullptr, list<Folder*> F = list<Folder*>(), list<File*> f = list<File*>(), bool h = false, time_t CTime = time(0))
	{
		name = n;
		path = p;
		parent = Parent;
		folders = F;
		files = f;
		hidden = h;

		folders = F;
		files = f;
		creationTime = CTime;

		Time = ctime(&CTime);
		ConvertTime(Time);
	}


	void ConvertTime(string& Time);
	void RemoveFile(string name);
	void RemoveFolder(string name);
	void EmptyDirectory();
	File* FindFile(string name);
	Folder* FindFolder(string name);
	void InsertFile(File* f);
	void InsertFolder(Folder* F);
	bool IsFolderExists(string name);

	void Print();
};


