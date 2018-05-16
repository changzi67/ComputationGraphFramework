#pragma once
#include <initializer_list>

template <typename T>
class BaseNode
{
protected:
	T value;
public:
	BaseNode(){}
	virtual ~BaseNode() = 0;
	T eval(const std::initializer_list<BaseNode<T>&>&);
	virtual T eval() = 0;
};
