#pragma once

#include "Op.h"

template <typename T>
class UniaryOp:public Op<T>
{
protected:
	BaseNode<T>* child;
public:

	UniaryOp():child(nullptr){}
	UniaryOp(BaseNode<T>* _child):child(_child){}
	UniaryOp(const BaseNode<T>& _child):child(&_child){}
	virtual T eval()=0;
	~UniaryOp(){}
	
};