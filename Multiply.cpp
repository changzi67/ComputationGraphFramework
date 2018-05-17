#include "Multiply.h"

template <typename T>
T Multiply<T>::eval(){
	if(this->evaled)
		return this->value;
	T ans = this->left->eval()*this->right->eval();
	this->value = ans;
	this->evaled = true;
	return ans;
}
