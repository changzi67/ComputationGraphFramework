#pragma once
#include "BinaryOp.h"

template <typename T>
class Divide: public BinaryOp<T>
{
public:
	Divide(){}
	Divide(BaseNode<T>* _left, BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Divide(BaseNode<T>& _left, BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Divide(){}
	
};