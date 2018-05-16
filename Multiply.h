#pragma once
#include "BinaryOp.h"

template <typename T>
class Multiply: public BinaryOp<T>
{
public:
	Multiply(){}
	Multiply(BaseNode<T>* _left, BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Multiply(BaseNode<T>& _left, BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Multiply(){}
	
};