#pragma once
#include "UniaryOp.h"
#include <iostream>
#include <string>

using std::string;

template<typename T>
class Print : public UniaryOp<T> 
{
	string name;
	static unsigned count;
public:
	Print(const string& _name = "");
	virtual ~Print(){}
	virtual T eval();
	string getName();
	void setName(const string &);
};

template<typename T>
unsigned Print<T>::count = 0;

