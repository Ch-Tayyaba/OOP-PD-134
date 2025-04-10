#include "Folder.h"
#include <iostream>
#include<iomanip>
#include"Tree.h"





void Folder::ConvertTime(string& Time)
{
	string AM_PM;
	string Date = Time.substr(8, 2);
	string Month = Time.substr(4, 3);
	string Day = Time.substr(0, 3);
	string Hour = Time.substr(11, 2);
	int Hr = stoi(Hour);
	if (Hr > 12)
	{
		Hr = Hr - 12;
		AM_PM = "PM";
	}
	else
	{
		AM_PM = "AM";
	}
	Hour = to_string(Hr);
	string Minute = Time.substr(14, 2);
	string Seconds = Time.substr(17, 2);
	string Year = Time.substr(20, 4);
	Time = "";
	Time = Month + " " + Date + "," + Year + "  " + Hour + ":" + Minute + ":" + Seconds + " " + AM_PM;
}

void Folder::RemoveFile(string name)
{
	list<File*>::iterator it;
	for (it = files.begin(); it != files.end(); it++)
	{
		if ((*it)->name == name)
		{
			files.erase(it);
			break;
		}
	}
	
}

void Folder::RemoveFolder(string name)
{
	list<Folder*>::iterator it;
	for (auto it = folders.begin(); it != folders.end(); it++)
	{
		if ((*it)->name == name)
		{
			folders.erase(it);
			break;
		}
	}
}

void Folder::EmptyDirectory()
{
	folders.clear();
	files.clear();
	
}

File* Folder::FindFile(string name)
{
	list<File*>::iterator it;
	for (it = files.begin(); it != files.end(); it++)
	{
		if ((*it)->name == name)
		{
			return (*it);
		}
	}
	return nullptr;
}

Folder* Folder::FindFolder(string name)
{
	list<Folder*>::iterator it;
	for (it = folders.begin(); it != folders.end(); it++)
	{
		if ((*it)->name == name)
		{
			return (*it);
		}
	}
	return nullptr;
}

void Folder::InsertFile(File* f)
{
	files.push_back(f);
}

void Folder::InsertFolder(Folder* F)
{
	folders.push_back(F);
}


bool Folder::IsFolderExists(string name)
{
	for (auto it = folders.begin(); it != folders.end(); ++it) {
		if ((*it)->name == name) {
			return true;
		}
	}
	return false;
}

void Folder::Print()
{
	if (folders.size() > 0 || files.size() > 0)
	{
		cout << "Directory of " << name << "  is :\n\n";
	}
	else
	{
		cout << "This Directory is Empty";
	}

	list<Folder*>::iterator iter;
	for (iter = folders.begin(); iter != folders.end(); iter++)
	{
		cout << left << setw(30) << (*iter)->Time << " <DIR>  " << (*iter)->name;
		cout << endl;
	}

	list<File*>::iterator it;
	for (it = files.begin(); it != files.end(); it++)
	{
		cout << left << setw(38) << (*it)->Time << (*it)->name << (*it)->extension;
		cout << endl;
	}
}

