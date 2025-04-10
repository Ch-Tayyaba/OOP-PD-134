#include "Dos.h"
#include<queue>
#include"CurrentFile.h"
#include<Windows.h>
#include"File.h"

void TreePrint(list<Folder*> folder, int num, int& y, int x);
void gotoxy(int x, int y);

void Dos::print()
{
    cout << "\t\t\t\t\t\t DSA | Tayyaba Afzal | 2022-CS-134  " << endl << endl;
    tree.Print();
}

void Dos::Run()
{
    print();
    bool exist = false;
    while (!exist)
    {
        exist = Input();
    }
}

bool Dos::Input()
{
	string command;
	getline(cin, command);
	string Operator = command.substr(0, command.find(' '));
	Operator = Lower(Operator);

	if (Operator == "mkdir")
	{
		Folder* f = new Folder(command.substr(6, command.length()), tree.current->path + "\\" + tree.current->name, tree.current);
		tree.current->InsertFolder(f);
		tree.SetPath(f);
		//tree.insert(new Folder(command.substr(6, command.length()), tree.current->path + "\\" + tree.current->name, tree.current));
	}
	else if (Operator == "create")
	{
		File* f = new File(command.substr(7, command.length()));
		tree.current->InsertFile(f);
	}
	else if (Operator == "del")
	{
		tree.current->RemoveFile(command.substr(4, command.length()));
	}
	else if (Operator == "cd")
	{
		string folder = command.substr(3, command.length());
		if (tree.current->IsFolderExists(folder))
		{
			tree.current = tree.current->FindFolder(folder);
		}
		else
		{
			cout << "No such directory exists! " << endl;
		}
	}
	else if (Operator == "cd..")
	{
		if (tree.current->parent != nullptr)
		{
			tree.current = tree.current->parent;
		}
	}
	else if (Operator == "cd\\")
	{
		if (tree.current->parent != nullptr)
		{
			tree.current = tree.root;
		}
	}
	else if (Operator == "dir" || Operator == "cd.")
	{
		tree.current->Print();
	}
	else if (Operator == "cls")
	{
		system("cls");
		print();
	}
	else if (Operator == "exit")
	{
		return true;
	}
	else if (Operator == "attrib")
	{
		string name = command.substr(7, command.length());
		File* f = tree.current->FindFile(name);
		cout << "Name: " << tree.current->name << "\t\t Path:" << tree.current->path << "\\" << tree.current->name;
		
	}
	else if (Operator == "format")
	{
		tree.current->EmptyDirectory();
	}
	else if (Operator == "rmdir")
	{
		Folder* curr = tree.current;
		tree.current = tree.current->parent;
		tree.current->RemoveFolder(curr->name);
	}
	else if (Operator == "prompt")
	{
		prompt = !prompt;
	}
	else if (Operator == "rename")
	{
		command = command.substr(Operator.length() + 1, command.length());
		string currentName = command.substr(0, command.find(' '));
		string newName = command.substr(currentName.length() + 1, command.length());
		File* f = tree.current->FindFile(currentName);
		f->name = newName;
	}
	else if (Operator == "copy")
	{
		command = command.substr(Operator.length() + 3, command.length());
		int nre = command.find(' ');
		string sourcePath = command.substr(0, command.find(' '));
		string destinationPath = command.substr(sourcePath.length() + 3, command.length());
		File* fileToCopy;

		Folder* currentFolder = tree.root;
		string f;
		while (sourcePath.length() > 0)
		{
			f = sourcePath.substr(0, sourcePath.find('\\'));
			sourcePath = sourcePath.substr(f.length() + 1, sourcePath.length());
			if (sourcePath.length() != 0)
			{
				currentFolder = currentFolder->FindFolder(f);
			}
			if (currentFolder == nullptr)
			{
				cout << "Path was not found!";
				return true;
			}
			
		}
		fileToCopy = currentFolder->FindFile(f);

		currentFolder = tree.root;
		while (destinationPath.length() > 0)
		{
			f = destinationPath.substr(0, destinationPath.find('\\'));
			destinationPath = destinationPath.substr(f.length() + 1, destinationPath.length());
			currentFolder = currentFolder->FindFolder(f);
			if (currentFolder == nullptr)
			{
				cout << "Path was not found!";
				return true;
			}
			currentFolder->InsertFile(fileToCopy);

		}
	}
	else if (Operator == "mov")
	{
		command = command.substr(Operator.length() + 3, command.length());
		int ind = command.find(' ');
		string srcPath = command.substr(0, command.find('\\'));
		string destPath = command.substr(srcPath.length() + 3, command.length());
		File* fileToMove;

		Folder* currFolder = tree.root;
		string f;
		while (srcPath.length() > 0)
		{
			f = srcPath.substr(0, srcPath.find(' '));
			if (currFolder == nullptr)
			{
				cout << "Path was not found!";
				return true;
			}
		}
		fileToMove = currFolder->FindFile(f);
		currFolder->RemoveFile(fileToMove->name);

		currFolder = tree.root;
		while (destPath.length() > 0)
		{
			f = destPath.substr(0, destPath.find('\\'));
			destPath = destPath.substr(f.length() + 1, destPath.length());
			currFolder = currFolder->FindFolder(f);
			if (currFolder == nullptr)
			{
				cout << "Path was not found!";
				return true;
			}
		}
		currFolder->InsertFile(fileToMove);

	}
	else if (Operator == "help")
	{
		cout << "ATTRIB		Displays file (name provided as input) attributes." << endl;
		cout << "CD 		Displays the name of or changes the current directory. See details below." << endl;
		cout << "CD. 		Prints working directory (i.e. your current directory in your tree structure)" << endl;
		cout << "CD.. 		Change directory to previous directory" << endl;
		cout << "CD\ 		Changes directory to root directory (i.e. V:\&gt;)" << endl;
		cout << "CONVERT 	Asks two types and converts extension of all files of one type to another type." << endl;
		cout << "COPY 		Copies one file in the current directory to another location (directory)." << endl;
		cout << "CREATE 	Creates a file with the name provided and allows the user to enter contents of the file." << endl;
		cout << "DEL 		Delete a file whose name is provided in input." << endl;
		cout << "DIR 		Displays a list of files and subdirectories in a directory." << endl;
		cout << "EDIT 		Opens a file (loads into a linked list) and allows the user to edit and save the contents of the file" << endl;
		cout << "FIND 		Searches for a file in your current virtual directory whose name is provided as input." << endl;
		cout << "FINDF 		Searches for a text string in the currently open file or the file whose name is provided as input." << endl;
		cout << "FINDSTR 	Searches for strings in all files of your current virtual directory, prints names of files with the string" << endl;
		cout << "FORMAT 	Formats the current virtual directory i.e. empties the current directory and all subdirectories." << endl;
		cout << "HELP 		Provides Help information for all these commands." << endl;
		cout << "LOADTREE 	Load a given tree in your tree structure. Given tree is in a file named tree.txt" << endl;
		cout << "MOVE 		Moves one file (whose name is provided as input) from one directory to another directory." << endl;
		cout << "PPRINT 	Adds a text file to the priority based print queue, and displays the current priority queue." << endl;
		cout << "PROMPT 	Changes the Windows command prompt (for example from V:\&gt; to V$)." << endl;
		cout << "PRINT 		Adds a text file to the print queue, and displays the current queue." << endl;
		cout << "PQUEUE 	Shows current state of the priority based print queue, with time left for each element" << endl;
		cout << "QUEUE 		Shows current state of the print queue, with time left for each element" << endl;
		cout << "RENAME 	Renames a file whose current and new name is provided as input." << endl;
		cout << "RMDIR 		Removes a directory along with its contents. Consider setting the respective sibling links" << endl;
		cout << "SAVE 		Saves the currently open file to disk." << endl;
		cout << "TREE 		Displays the complete directory structure." << endl;
		cout << "VER 		Displays the version of your program." << endl;
		cout << "PWD 		Prints working directory" << endl;
		cout << "MKDIR 		Creates a virtual directory." << endl;
		cout << "EXIT 		Quits the program" << endl;
	}
	else if (Operator == "ver")
	{
		cout << "Microsoft Windows [Version 10.0.22621.2861]";
	}
	else if (Operator == "find")
	{
		string name = command.substr(5, command.length());
		File* f = tree.current->FindFile(name);
		if (f != nullptr)
		{
			cout << "File Exists.";
		}
	}
	else if (Operator == "edit")
	{
		string name = command.substr(4, command.length());
		File* f = tree.current->FindFile(name);
		if (f == nullptr)
		{
			File* f = new File(name);
			tree.current->InsertFile(f);
		}
		ofstream Wrt;
		f->edit->EditFile(Wrt);
		
	}
	else if (Operator == "tree")
	{
		system("cls");
		print();
		cout << "V";
		int y = 3;
		TreePrint(tree.root->folders,1,y,10);
	}
	else if (Operator == "pwd")
	{
		cout << "Name: " << tree.current->name << "\t\tPath:" << tree.current->path << "/" << tree.current->name;
	}
	else if (Operator == "pqueue")
	{
		priority_queue<File*> filePQueue;
		for (auto& f : tree.current->files)
		{
			filePQueue.push(f);
		}
		while (!filePQueue.empty()) {
			File* currentFile = filePQueue.top();
			cout << "Name: " << currentFile->name << ", Size: " << currentFile->size << endl;
			filePQueue.pop();
		}
	}
	else if (Operator == "queue")
	{
		int x = 1;
		while (!fileQueue.empty())
		{
			cout << x << " " << fileQueue.front()->name << endl;
			fileQueue.pop();
			x++;
		}
	}
	else if (Operator != "cls")
	{
		if (prompt)
		{
			tree.Print("$");
		}
		else
		{
			tree.Print();
		}
		return false;
		}

	return false;
}

string Dos::Lower(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
    return str;
}
void TreePrint(list<Folder*> folder, int num, int& y, int x)
{
	for (auto it = folder.begin(); it != folder.end(); it++)
	{
		gotoxy(x, y);
		cout << "|_____" << (*it)->name << endl;
		if (!(*it)->folders.empty())
		{
			y++;
			TreePrint((*it)->folders, num + 3, y, x + 5);
		}
		y++;
	}
}
void gotoxy(int x, int y) {
	COORD coord; 
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
