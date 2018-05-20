#pragma once
#include "Op.h"

template<typename T>
class BinaryOp : public Op<T>
{
protected:
	BaseNode<T>* left;
	BaseNode<T>* right;
public:
	BinaryOp():left(nullptr),right(nullptr){}
	BinaryOp(BaseNode<T>* _left,BaseNode<T>* _right):left(_left),right(_right){}
	BinaryOp(BaseNode<T>& _left,BaseNode<T>& _right):left(&_left),right(&_right){}
	virtual T eval() =0;
	~BinaryOp(){}
	
};