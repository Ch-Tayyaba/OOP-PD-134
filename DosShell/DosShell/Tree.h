#pragma once
#include "Folder.h"
#include"File.h"
#include<string>
#include<ctime>
#include<time.h>

class Tree
{
public:
	Folder* root;
	Folder* current;
	Tree()
	{
		current = root = new Folder("V");
	}
	void insert(Folder* F);
	void SetPath(Folder* F);
	void Print(string prompt = "\\>");

	void SaveTree();
	void GoThroughAllTree();
	void GoThroughAllTree(Folder* CurrentFolder);
};