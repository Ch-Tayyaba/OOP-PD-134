#include "CurrentFile.h"
#include"State.h"
#include<conio.h>
#include<windows.h>

list<string> files;

void gotoRowCol(int rpos, int cpos)
{
	COORD coord;
	coord.X = rpos;
	coord.Y = cpos;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



State CurrentFile::SaveState()
{
		State* s = new State();
		s->text.push_back(list<char>());
		auto r_itr = s->text.begin();
		for (auto row = text.begin(); row != text.end(); row++, r_itr++)
		{
			s->text.push_back(list<char>());
			for (auto col = (*row).begin(); col != (*row).end(); col++)
			{
				char ch = *col;
				(*r_itr).push_back(ch);
			}
		}
		s->riter = s->text.begin();
		s->citer = (*s->riter).begin();
		s->c = currCol;
		s->r = currRow;
		return *s;
}
void CurrentFile::LoadState(State s)
{
	text = s.text;
	riter = text.begin();
	currCol = s.c;
	currRow = s.r;
	for (int r = 0; r < s.r; r++)
	{
		riter++;
	}
	citer = (*riter).begin();
	for (int c = 0; c < s.c; c++)
	{
		citer++;
	}
}
void CurrentFile::Choice(ifstream& Rdr)
{
	int choice = -1;
	int R = 0, C = 0;
}
void CurrentFile::Closing(ifstream& Rdr)
{
	Rdr.close();

	ofstream wtr;
	wtr.open("SaveFile.txt");
	for (auto i = files.begin(); i != files.end(); i++)
	{
		wtr << (*i) << endl;
	}
	wtr.close();
}


void CurrentFile::_CreateFile()
{
	system("cls");
	string fileName;
	cout << "Enter File Name";
	cin >> fileName;
	if (find(files.begin(), files.end(), fileName) != files.end())
	{
		cout << "File Already exist\n";
		return;
	}
	files.push_back(fileName);

	ofstream Wrt(fileName.c_str());

	system("cls");
	EditFile(Wrt);
	system("cls");
	system("color 09");
	Wrt.close();

}
void CurrentFile::OpenFile()
{
	system("cls");
	string fileName;
	cout << "Enter File Name";
	cin >> fileName;
	if (find(files.begin(), files.end(), fileName) == files.end())
	{
		cout << "File does not exist\n";
		return;
	}
	ifstream Rdr(fileName.c_str());
	OpenSavedFile(Rdr);
	Rdr.close();

	ofstream Wrt(fileName.c_str());
	system("cls");
	print();
	gotoRowCol(currRow, currCol);
	EditFile(Wrt);
	system("cls");
	system("color 09");



}

void CurrentFile::EditFile(ofstream& Wrt)
{
	system("Color F0");
	char c;
	c = _getch();
	gotoRowCol(currRow, currCol);
	cout << c;
	(*citer) = c; 
	currCol++;

	while (true)
	{
		if (currRow == 0)
		{
			gotoRowCol(currRow, currCol);
		}
		else
		{
			gotoRowCol(currRow, currCol + 1);
		}

		c = _getch();

		if (c == -32)
		{
		A:
			c = _getch();
			if (c == 72)
			{
				if (currRow == 0)
				{
					continue;
				}
				riter--;
				citer = (*riter).begin();
				currRow--;
				currCol = 0;
			}
			else if (c == 80)
			{
				riter++;
				citer = (*riter).begin();
				currRow++;
				currCol = 0;
			}
			else if (c == 75)
			{
				if (currCol - 1 > 0)
				{
					citer--;
					currCol--;
				}
			}
			else if (c == 77)
			{
				if (currCol == 159)
				{
					continue;
				}
				citer++;
				currCol++;
			}
			else if (c == 83)
			{
				auto temp = citer;
				citer++;
				(*riter).erase(citer);
				citer = temp;
				system("cls");
				print();
				UpdateUndo();
			}
			if (currCol == 0)
			{
				gotoRowCol(currRow, 0);
				c = _getch();
				if (c == -32)
				{
					goto A;
				}
				(*riter).push_back(c);
				citer = (*riter).begin();
				currCol = 1;
				system("cls");
				print();
				UpdateUndo();
			}
			continue;
		}
		else if (c == 13)
		{
			auto temp = riter;
			riter++;
			text.insert(riter, list<char>());
			riter = ++temp;
			currRow++;
			currCol = 0;
			gotoRowCol(currRow, currCol);
			c = _getch();
			if (c == -32)
			{
				goto A;
			}
			(*riter).push_back(c);
			citer = (*riter).begin();
			system("cls");
			print();
			UpdateUndo();
			continue;
		}
		else if (c == 8)
		{
			if (currCol == 0)
			{
				gotoRowCol(currRow, 0);
				c = _getch();
				if (c == -32)
				{
					goto A;
				}
				if (c == 8)
				{
					continue;
				}
				(*citer) = c;
				citer = (*riter).begin();
				currCol = 1;
				continue;
			}
			auto temp = --citer;
			citer++;
			(*riter).erase(citer);
			citer = temp;
			currCol--;
			system("cls");
			print();
			UpdateUndo();
			continue;
		}
		else if (c == 26)
		{
			undo.pop_back();
			if (!undo.empty())
			{
				State s = undo.back();
				LoadState(s);
				redo.push(undo.back());
				undo.pop_back();
				system("cls");
				print();
			}
			continue;
		}
		else if (c == 72)
		{
			WriteTextToFile(Wrt);
			break;
		}

		if (currCol == 159)
		{
			text.push_back(list<char>());
			riter++;
			currCol = 0;
			currRow++;
			(*riter).push_back(c);
			citer = (*riter).begin();
		}
		else
		{
			if (currRow == 0 && currCol == -1)
			{
				(*citer) = c;
				currCol++;
			}
			else
			{
				auto temp = citer;
				citer++;

				(*riter).insert(citer, c);
				citer = ++temp;
				currCol++;
			}
		}
		system("Color 07");
	}
}

void CurrentFile::print()
{
	for (auto r = text.begin(); r != text.end(); r++)
	{
		for (auto c = (*r).begin(); c != (*r).end(); c++)
		{
			cout << *c;
		}
		cout << endl;
	}
}
void CurrentFile::UpdateUndo()
{
	if (undo.size() > 5)
	{
		undo.erase(undo.begin());
	}
	State s;
	s = SaveState();
	undo.push_back(s);
}
void CurrentFile::OpenSavedFile(ifstream&  Rdr)
{
	char ch;
	Rdr >> ch;

	while(!Rdr.eof())
	{
		Rdr.get(ch);
		if (ch != '\n')
		{
			(*riter).push_back(ch);
		}
		else
		{
			text.push_back(list<char>());
			riter++;
		}
	}
	riter = text.begin();
	citer = (*riter).begin();
	currRow = 0;
	currCol = 0;
	gotoRowCol(currRow, currCol);
}
void CurrentFile::WriteTextToFile(ofstream& Wrt)
{
	for (auto r = text.begin(); r != text.end(); r++)
	{
		for (auto c = (*r).begin(); c != (*r).end(); c++)
		{
			Wrt << *c;
		}
		Wrt << '\n';
	}
}
void Input(ifstream& Rdr)
{
	string fn;
	Rdr >> fn;

	while (!Rdr.eof())
	{
		files.push_back(fn);
		Rdr >> fn;
	}
}