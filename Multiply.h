#pragma once
#include "BinaryOp.h"

template <typename T>
class Multiply: public BinaryOp<T>
{
public:
	using BaseNode<T>::eval;
	Multiply(){}
	Multiply(BaseNode<T>* _left,BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Multiply(BaseNode<T>& _left,BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Multiply(){}
	
};

template <typename T>
T Multiply<T>::eval(){
	if(this->getTime()>=BaseNode<T>::currentTime)
		return this->value;
	T ans = this->left->eval()*(this->right->eval());
	this->value = ans;
	this->timeStamp = BaseNode<T>::currentTime;
	return ans;
}
