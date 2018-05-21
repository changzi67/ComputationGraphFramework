#pragma once
#include "BaseNode.h"

template<typename T>
class Op: public BaseNode<T>
{
public:
	Op(){}
	virtual T eval()= 0;
	virtual ~Op(){};
};
