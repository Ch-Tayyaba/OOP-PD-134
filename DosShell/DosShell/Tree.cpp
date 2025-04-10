#include "Tree.h"
#include <iostream>
#include<string.h>
#include"File.h"
#include"Folder.h"
#include<fstream>

void Tree::insert(Folder* F)
{
    current->folders.push_back(F);
}

void Tree::SetPath(Folder* F)
{
    string path = current->name;
    Folder* parent = new Folder();
    while (parent != nullptr)
    {
        path = parent->name + "/" + path;
        parent = parent->parent;
    }
    F->path = path;
}

void Tree::Print(string prompt)
{
    if (current->name == "V")
    {
        cout << "V:" << prompt;
    }
    else
    {
        cout << "V:" << current->path.substr(2, current->path.length()) << "\\" << current->name << prompt;
    }
}



void Tree::SaveTree()
{
	ofstream F("Tree.txt");
	list<Folder*>SaveList;
	Folder* Temp;
	/// /////////
	SaveList.push_back(root);
	SaveList.push_back(nullptr);

	/////////////////////////////
	list<Folder*>::iterator SaveIT;
	////////////////////////////

	for (SaveIT = SaveList.begin(); SaveIT != SaveList.end(); SaveIT++)
	{
		if (*SaveIT == nullptr)
		{
			continue;
		}
		Temp = *SaveIT;
		F << Temp->name;
		list<Folder*>::iterator it;
		for (it = Temp->folders.begin(); it != Temp->folders.end(); it++)
		{
			SaveList.push_back(*it);
			F << "Dir" << (*it)->name << ",";
		}
	}
	cout << endl;
}
void Tree::GoThroughAllTree(Folder* CurrentFolder)
{
	if (CurrentFolder->folders.size() == 0)
	{
		return;
	}
	for (auto t = CurrentFolder->folders.begin(); t != CurrentFolder->folders.end(); t++)
	{
		GoThroughAllTree(*t);
		cout << (*t)->name << " ";
	}
	cout << endl;
}
void Tree::GoThroughAllTree()
{
	GoThroughAllTree(root);
}


