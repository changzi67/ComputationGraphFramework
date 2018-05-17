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
	BaseNode<T>& operator + (const BaseNode<T>& b);
	BaseNode<T>& operator - (const BaseNode<T>& b);
	BaseNode<T>& operator * (const BaseNode<T>& b);
	BaseNode<T>& operator / (const BaseNode<T>& b);

};
