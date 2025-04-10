#pragma once
#include<iostream>
#include<list>

using namespace std;

class State
{
public:
	list<list<char>> text;
	list<list<char>>::iterator riter;
	list<char>::iterator citer;
	int r, c;
};

