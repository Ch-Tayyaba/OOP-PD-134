#include "File.h"

void File::Print()
{

}
void File::ConvertTime(string& Time)
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
void File::CreationOfFile()
{
	ofstream FileCreator(name + extension);
	if (FileCreator.is_open())
	{
		cout << "File Created";
		FileCreator.close();
	}
	else
	{
		cout << "File Not created";
	}
}
