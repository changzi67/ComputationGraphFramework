#pragma once
#include "BaseNode.h"

template<typename T>
class Op: public BaseNode<T>
{
protected:
	bool evaled;
public:
	Op():evaled(false){}
	virtual T eval()= 0;
	virtual ~Op(){};
};
