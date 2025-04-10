#pragma once
#include<list>
#include<queue>
#include<stack>
#include"State.h"
#include<fstream>

using namespace std;


class CurrentFile
{
public:
	int currRow, currCol;
	list<list<char>> text;
	list<list<char>>::iterator riter;
	list<char>::iterator citer;
	deque<State> undo;
	stack<State> redo;
	CurrentFile()
	{
		text.push_back(list<char>());
		riter = text.begin();
		(*riter).push_back(' ');
		citer = (*riter).begin();
		currRow = 0;
		currCol = 0;

	}
	State SaveState();
	void LoadState(State s);
	void Choice(ifstream& Rdr);
	void Closing(ifstream& Rdr);
	void _CreateFile();
	void OpenFile();
	void EditFile(ofstream& Wrt);
	void OpenSavedFile(ifstream& Rdr);
	void WriteTextToFile(ofstream& Wrt);
	void print();
	void UpdateUndo();
};

