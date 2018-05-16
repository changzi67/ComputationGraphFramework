#pragma once
#include "BaseNode.h"

template <typename T>
class Parameter: public BaseNode<T>
{
public:
	Parameter(){}
	Parameter(const T& data):Parameter::value(data){}
	virtual T eval();
	void set(const T& data);
	void add(const T& data);
	void minus(const T& data);
	void multiply(const T& data);
	void divide(const T& data);
	~Parameter(){}
};
