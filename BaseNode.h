#pragma once
#include <initializer_list>
#include <tuple>

template<typename T>
class Op;

template<typename T>
class BinaryOp;

template<typename T>
class Add;

template<typename T>
class Sub;

template<typename T>
class Multiply;

template<typename T>
class Divide;

template<typename T>
class Placeholder;

template <typename T>
class BaseNode
{
protected:
	T value;
public:
	BaseNode(){}
	virtual ~BaseNode(){};
	T eval(const std::initializer_list<std::pair<Placeholder<T>&,const T&>>);
	virtual T eval()= 0;
	
	Add<T>& operator + (BaseNode<T>& b);
	Sub<T>& operator - (BaseNode<T>& b);
	Multiply<T>& operator * (BaseNode<T>& b);
	Divide<T>& operator / (BaseNode<T>& b);

};

#include "Placeholder.h"
#include "Add.h"
#include "Sub.h"
#include "Multiply.h"
#include "Divide.h"

#include <initializer_list>
#include <string>
#include <iostream>
#include <tuple>


//using initializer list to support something like t.eval({{x,1},{y,2}});
template<typename T>
T BaseNode<T>::eval(const std::initializer_list<std::pair<Placeholder<T>&,const T&>> vars){
	for(auto it = vars.begin();it!=vars.end();++it){
		if(!((it->first).isAssigned()))
			it->first = it->second;
		else std::cout<<"Error: Placeholder "<<(it->first).getName()<<" appeared more than once!";
		return T();
	}
	try{
		T ans = eval();
		for(auto it = vars.begin();it!=vars.end();++it){
			(it->first).setAssigned(false);
		}
		return ans;
	}
	catch(const std::string & s){
		std::cout<<"Error: Placeholder "<<s<<"not found!"<<std::endl;
	}
	
}

template<typename T>
Add<T>& BaseNode<T>::operator + (BaseNode<T>& b){
	auto x = new Add<T>(*this,b);
	return *x;
}
template<typename T>
Sub<T>& BaseNode<T>::operator - (BaseNode<T>& b){
	auto x = new Sub<T>(*this,b);
	return *x;
}
template<typename T>
Multiply<T>& BaseNode<T>::operator * (BaseNode<T>& b){
	auto x = new Multiply<T>(*this,b);
	return *x;
}
template<typename T>
Divide<T>& BaseNode<T>::operator / (BaseNode<T>& b){
	auto x = new Divide<T>(*this,b);
	return *x;
}
