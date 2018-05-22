#pragma once
#include "BinaryOp.h"

template <typename T>
class Sub: public BinaryOp<T>
{
public:
	using BaseNode<T>::eval;
	Sub(){}
	Sub(BaseNode<T>* _left,BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Sub(BaseNode<T>& _left,BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Sub(){}
	
};

template <typename T>
T Sub<T>::eval(){
	if(this->evaled)
		return this->value;
	BaseNode<T>::ops.insert(this);
	T ans = this->left->eval()-(this->right->eval());
	this->value = ans;
	this->evaled = true;
	return ans;
}
