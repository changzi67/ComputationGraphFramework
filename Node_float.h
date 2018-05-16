#pragma once
#include "BaseNode.h"

template<>
class BaseNode<float>
{
protected:
	float value;
public:
	BaseNode<float>& operator + (const BaseNode<float>& b);
	BaseNode<float>& operator - (const BaseNode<float>& b);
	BaseNode<float>& operator * (const BaseNode<float>& b);
	BaseNode<float>& operator / (const BaseNode<float>& b);

};
