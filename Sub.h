#pragma once
#include "BinaryOp.h"

template <typename T>
class Sub: public BinaryOp<T>
{
public:
	Sub(){}
	Sub(BaseNode<T>* _left, BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Sub(BaseNode<T>& _left, BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Sub(){}
	
};