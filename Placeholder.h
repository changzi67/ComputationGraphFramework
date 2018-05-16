#pragma once
#include "BaseNode.h"
#include <string>

using std::string;


template <typename T>
class Placeholder :public BaseNode<T>
{
	bool assigned;
	string name;
	static int count;
public:
	Placeholder(const string& _name="");
	virtual T eval();
	virtual ~Placeholder(){}
	void setAssigned(bool status);
	const Placeholder& operator =(const T& data);
	string getName();
	void setName(const string &);
};

template<typename T>
int Placeholder<T>::count = 0;
