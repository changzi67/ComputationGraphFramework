#pragma once
#include "BinaryOp.h"
template <typename T>
class Add: public BinaryOp<T>
{
public:
	using BaseNode<T>::eval;
	Add(){}
	Add(BaseNode<T>* _left,BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Add(BaseNode<T>& _left,BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Add(){}
	
};

template <typename T>
T Add<T>::eval(){
	if(this->getTime()>=BaseNode<T>::currentTime)
		return this->value;
	T ans = this->left->eval()+(this->right->eval());
	this->value = ans;
	this->timeStamp = BaseNode<T>::currentTime;
	return ans;
}
