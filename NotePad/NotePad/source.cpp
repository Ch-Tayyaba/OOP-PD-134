#include<list>
#include<Windows.h>
#include <iostream>
#include <fstream>
#include<stack>
#include<deque>
#include<string>
#include<string.h>
#include <conio.h>

using namespace std;

void get_Row_Colsbylclick(int& rowpos, int& colpos)
{
	char key = _getch();

	switch (key) {
	case 72: // Up arrow key
		rowpos--;
		break;
	case 80: // Down arrow key
		rowpos++;
		break;
	case 75: // Left arrow key
		colpos--;
		break;
	case 77: // Right arrow key
		colpos++;
		break;
	}

}
void gotoRows_Cols(int rowpos, int colpos)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { static_cast<SHORT>(colpos), static_cast<SHORT>(rowpos) };
	SetConsoleCursorPosition(hConsole, position);

}

list<string> File;
struct shape
{
	list<list<char>>text;
	list<list < char >> ::iterator row_iter;
	list<char>::iterator col_iter;
	int rows;
	int cols;
};
class current_File
{
public:
	int currRow, currCol;
	list<list<char>>text;
	list<list<char>>::iterator row_iter;
	list<char>::iterator col_iter;
	deque<shape> undo;
	stack <shape> redo;
	current_File()
	{
		text.push_back(list<char>());
		row_iter = text.begin();
		(*row_iter).push_back(' ');
		col_iter = (*row_iter).begin();
		currRow = 0;
		currCol = 0;
	}
	shape save_state()
	{
		shape* sh = new shape;
		sh->text.push_back(list<char>());
		auto riter = sh->text.begin();
		for (auto row = text.begin(); row != text.end(); row++, riter++)
		{
			sh->text.push_back(list<char>());
			for (auto col = (*row).begin(); col != (*row).end(); col++)
			{
				char ch = *col;
				(*riter).push_back(ch);
			}
		}
		sh->row_iter = sh->text.begin();
		sh->col_iter = (*sh->row_iter).begin();
		sh->cols = currCol;
		sh->rows = currRow;
		return *sh;
	}
	void Load(shape h)
	{
		text = h.text;
		row_iter = text.begin();
		currCol = h.cols;
		currRow = h.rows;
		for (int rows = 0; rows < h.rows; rows++)
			row_iter++;
		col_iter = (*row_iter).begin();
		for (int cols = 0; cols < h.cols; cols++)
			currCol++;
	}
	void create_File()
	{
		system("cls");
		string fileName = "";
		cout << "ENTER THE NAME OF FILE: ";
		cin >> fileName;
		fileName += ".txt";
		if (Is_File_Exist(fileName, File))
		{
			cout << "THIS FILE ALREADY EXISTS\n ";
			return;
		}

		//File.Insert(fileName.c_str());
		ofstream Wrt(fileName.c_str());
		File.push_back(fileName);
		system("cls");
		edit_text(Wrt);
		system("cls");
		system("Color 09");
		Wrt.close();
	}
	void open_File()
	{
		system("cls");
		string name;
		cout << "ENTER NAME OF FILE : ";
		cin >> name;
		if (!Is_File_Exist(name, File))
		{
			cout << "Does not exist";
			return;
		}
		ifstream Reader(name.c_str());
		open_savedfile(Reader);
		Reader.close();
		ofstream Wrt(name.c_str());
		system("cls");
		print();
		gotoRows_Cols(currRow, currCol);
		edit_text(Wrt);
		system("cls");
		system("color 09");
		Wrt.close();
	}
	void edit_text(ofstream& Wrt)
	{
		system("Color 09");
		char temp;
		temp = _getch();
		gotoRows_Cols(currRow, currCol);
		cout << temp;
		(*col_iter) = temp;
		currCol++;
		while (true)
		{
			if (currRow == 0)
			{
				gotoRows_Cols(currRow, currCol);
			}
			else
				gotoRows_Cols(currRow, currCol + 1);
			temp = _getch();
			if (temp == -32)
			{
			A:
				temp = _getch();
				if (temp == 72)// for up key
				{
					if (currRow == 0)
						continue;
					row_iter--;
					col_iter = (*row_iter).begin();
					currRow--;
					currCol = 0;
				}
				else if (temp == 80)// for down key
				{
					row_iter++;
					col_iter = (*row_iter).begin();
					currRow++;
					currCol = 0;
				}
				else if (temp == 75) // for left key
				{
					if (currCol - 1 > 0)
					{
						col_iter--;
						currCol--;
					}
				}
				else if (temp == 77) // for right key
				{
					if (currCol == 159)
						continue;
					col_iter++;
					currCol++;
				}
				else if (temp == 83) // for delete key
				{
					auto temp2 = col_iter;
					col_iter++;
					(*row_iter).erase(col_iter);
					col_iter = temp2;
					system("cls");
					print();
					update_undo();

				}
				if (currCol == 0)
				{
					gotoRows_Cols(currRow, 0);
					temp = _getch();
					if (temp == -32)
						goto A;
					(*row_iter).push_front(temp);
					col_iter = (*row_iter).begin();
					currCol = 1;
					system("cls");
					print();
					update_undo();
				}
				continue;
			}
			else if (temp == 13) // for enter key
			{
				auto temp2 = row_iter;
				row_iter++;
				text.insert(row_iter, list<char>());
				row_iter = ++temp2;
				currRow++;
				currCol = 0;
				gotoRows_Cols(currRow, currCol);
				temp = _getch();
				if (temp == -32)
					goto A;
				(*row_iter).push_back(temp);
				col_iter = (*row_iter).begin();
				system("cls");
				print();
				update_undo();
				continue;
			}
			else if (temp == 8) // for backspace key
			{
				if (currCol == 0)
				{
					if (currRow > 0)
					{
						// Merge current line with the previous line
						auto temp2 = row_iter;
						temp2--;
						(*temp2).insert((*temp2).end(), (*row_iter).begin(), (*row_iter).end());
						row_iter = text.erase(row_iter);
						currRow--;
						row_iter = temp2;
						currCol = temp2->size();
					}
				}
				else
				{
					auto temp2 = --col_iter;
					col_iter++;
					(*row_iter).erase(col_iter);
					col_iter = temp2;
					currCol--;
				}

				// Redraw only the affected portion of the screen
				system("cls");
				print();
				update_undo();
				continue;
			}

			else if (temp == 26) // for undo 
			{
				if (!undo.empty())
				{
					shape s = undo.back();
					Load(s);
					redo.push(undo.back());
					undo.pop_back();
					currCol = 0;
					currRow = 0;
					system("cls");
					print();
				}
				continue;
			}
			else if (temp == 25) // for redo 
			{
				if (!redo.empty())
				{
					undo.push_back(redo.top());
					shape s = redo.top();
					redo.pop();
					Load(s);
					currCol = 0; currRow = 0;
					system("cls");
					print();

				}
				continue;
			}
			else if (temp == 9)
			{
				save_state();
				write_textin_file(Wrt);
				Wrt << '\n';
			}
			else if (temp == 27) // for esc to close it
			{
				write_textin_file(Wrt);
				break;
			}
			if (currCol == 159)
			{
				text.push_back(list<char>());
				row_iter++;
				currCol = 0;
				currRow++;
				(*row_iter).push_back(temp);
				col_iter = (*row_iter).begin();
			}
			else
			{
				auto temp2 = col_iter;
				col_iter++;
				(*row_iter).insert(col_iter, temp);
				col_iter = ++temp2;
				currCol++;
			}
			system("cls");
			print();
			update_undo();
		}
		//gotoRows_Cols(currRow, currCol);
		system("Color 09");
	}
	void print()
	{
		for (auto rows = text.begin(); rows != text.end(); rows++)
		{
			for (auto cols = (*rows).begin(); cols != (*rows).end(); cols++)
			{
				cout << *cols;
			}
			cout << endl;
		}
	}
	void update_undo()
	{
		if (undo.size() > 5)
			undo.erase(undo.begin());
		shape s;
		s = save_state();
		undo.push_back(s);
	}
	void closed(ifstream& Reader)
	{
		Reader.close();
		ofstream wtr;
		wtr.open("F:\\SEM 3\\DSA\\DOS_SHELL\\DOS_SHELL\\Saved.txt");
		for (auto i = File.begin(); i != File.end(); i++)
		{
			wtr << (*i) << endl;
		}
		wtr.close();
	}
	void write_textin_file(ofstream& wtr)
	{
		for (auto rows = text.begin(); rows != text.end(); rows++)
		{
			for (auto cols = (*rows).begin(); cols != (*rows).end(); cols++)
			{
				wtr << *cols;
			}
			wtr << '\n';
		}
	}
	void open_savedfile(ifstream& rdr)
	{
		char c;
		while (rdr.get(c))
		{
			if (c != '\n')
			{
				(*row_iter).push_back(c);
			}
			else
			{
				text.push_back(list<char>());
				row_iter = text.end();
			}
		}
		if (text.back().empty() && c != '\n')
		{
			text.pop_back();
			row_iter = text.end();
		}
		row_iter = text.begin();
		col_iter = (*row_iter).begin();
		currRow = 0;
		currCol = 0;
		gotoRows_Cols(currRow, currCol);
	}
	bool Is_File_Exist(string file, const list<string>& File)
	{
		for (const string& str : File) {
			if (file == str) {
				return true;
			}
		}
		return false;
	}
};
void input(ifstream& Reader)
{
	string fun;
	Reader >> fun;
	while (!Reader.eof())
	{
		File.push_back(fun);
		Reader >> fun;
	}
}
int Options()
{
	cout << "1. create file" << endl;
	cout << "2. exit" << endl;
	int options;
	cout << endl;
	cout << "enter option: ";
	cin >> options;
	return options;
}
int main()
{
	system("color 09");
	int rows = 0;
	int cols = 0;
	current_File C;
	ifstream Reader;
	ofstream writer;
	int choice = Options();
	if (choice == 1)
	{
		C.create_File();
	}
	else if (choice == 2)
	{
		cout << "press any key to continue...";
	}
	

	Reader.open("F:\\SEM 3\\DSA\\DOS_SHELL\\DOS_SHELL\\Saved.txt");
	writer.open("F:\\SEM 3\\DSA\\DOS_SHELL\\DOS_SHELL\\RECENTFILE.txt");
	input(Reader);
	//while (true)
	//{
	//	C.option(Reader);
	//}
	Reader.close();
	//return getch();
}
