#pragma once

#include "BaseNode.h"

template<typename T>
class Constant : public BaseNode<T>
{
public:
	Constant(){}
	Constant(T _value){
		this->value = _value;
	}
	virtual T eval(){
		return this->value;
	}
	virtual ~Constant(){}
};