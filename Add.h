#pragma once
#include "BinaryOp.h"

template <typename T>
class Add: public BinaryOp<T>
{
public:
	Add(){}
	Add(BaseNode<T>* _left, BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Add(BaseNode<T>& _left, BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Add(){}
	
};