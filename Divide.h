#pragma once
#include "BinaryOp.h"

template <typename T>
class Divide: public BinaryOp<T>
{
public:
	
	using BaseNode<T>::eval;
	Divide(){}
	Divide(BaseNode<T>* _left,BaseNode<T>* _right):BinaryOp<T>(_left,_right){}
	Divide(BaseNode<T>& _left,BaseNode<T>& _right):BinaryOp<T>(_left,_right){}
	virtual T eval();
	~Divide(){}
	
};

template <typename T>
T Divide<T>::eval(){
	if(this->getTime()>=ComputationGraph::currentTime)
		return this->value;
	T ans = this->left->eval()/(this->right->eval());
	this->value = ans;
	this->timeStamp = ComputationGraph::currentTime;
	return ans;
}
