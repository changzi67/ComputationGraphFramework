#include "Sub.h"

template <typename T>
T Sub<T>::eval(){
	if(this->evaled)
		return this->value;
	T ans = this->left->eval()-this->right->eval();
	this->value = ans;
	this->evaled = true;
	return ans;
}