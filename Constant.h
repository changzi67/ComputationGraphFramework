#pragma once

#include "BaseNode.h"

template<typename T>
class Constant : public BaseNode<T>
{
	using BaseNode<T>::value;
public:
	Constant(){}
	Constant(T _value){
		value = _value;
	}
	virtual T eval(){
		return value;
	}
	virtual ~Constant(){}
};