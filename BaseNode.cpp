#include "BaseNode.h"
#include "Placeholder.h"
#include "Add.h"
#include "Sub.h"
#include "Multiply.h"
#include "Divide.h"

#include <initializer_list>
#include <string>
#include <iostream>


//using initializer list to support something like t.eval({x=1,y=2});
template<typename T>
T BaseNode<T>::eval(const std::initializer_list<BaseNode<T>&>& vars){
	try{
		T ans = eval();
		for(auto it = vars.begin();it!=vars.end();++it){
			*it.setAssigned(false);
		}
		return ans;
	}
	catch(const string & s){
		std::cout<<"Error: Placeholder "<<s<<"not found!"<<std::endl;
	}
	
}

template<typename T>
BaseNode<T>& BaseNode<T>::operator + (const BaseNode<T>& b){
	return Add<T>(*this,b);
}
template<typename T>
BaseNode<T>& BaseNode<T>::operator - (const BaseNode<T>& b){
	return Sub<T>(*this,b);
}
template<typename T>
BaseNode<T>& BaseNode<T>::operator * (const BaseNode<T>& b){
	return Multiply<T>(*this,b);
}
template<typename T>
BaseNode<T>& BaseNode<T>::operator / (const BaseNode<T>& b){
	return Divide<T>(*this,b);
}

