#include<iostream>
#include"Dos.h"
#include"CurrentFile.h"
#include<fstream>

using namespace std;

int main()
{
	Dos DosShell;

	DosShell.Run();

	/*system("color 09");
	int r = 0, c = 0;
	CurrentFile N;
	ifstream Rdr;
	ofstream Wtr;
	Rdr.open("SaveFile.txt");
	Wtr.open("recentFile.txt");
	Input(Rdr);
	while(true)
	{
		N.Choice(Rdr);
	}
	Rdr.close();*/


	return 0;
}