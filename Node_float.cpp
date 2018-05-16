#include "Node_float.h"
#include "Add.h"
#include "Sub.h"
#include "Multiply.h"
#include "Divide.h"

template<>
BaseNode<float>& BaseNode<float>::operator + (const BaseNode<float>& b){
	return Add<float>(*this,b);
}
template<>
BaseNode<float>& BaseNode<float>::operator - (const BaseNode<float>& b){
	return Sub<float>(*this,b);
}
template<>
BaseNode<float>& BaseNode<float>::operator * (const BaseNode<float>& b){
	return Multiply<float>(*this,b);
}
template<>
BaseNode<float>& BaseNode<float>::operator / (const BaseNode<float>& b){
	return Divide<float>(*this,b);
}
