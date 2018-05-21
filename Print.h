#pragma once
#include "UniaryOp.h"
#include <iostream>
#include <string>

using std::string;

template<typename T>
class Print : public UniaryOp<T> 
{	
	string name;
	static unsigned count;
public:
	Print(BaseNode<T>& _child, const string& _name = "");
	Print(BaseNode<T>* _child, const string& _name = "");
	virtual ~Print(){}
	virtual T eval();
	string getName();
	void setName(const string &);
};

template<typename T>
unsigned Print<T>::count = 0;

#include <sstream>

using std::string;

template<typename T>
Print<T>::Print(BaseNode<T>& _child, const string& _name):name(_name){
	Print<T>::child=& _child;
	Print<T>::count++;
	if(_name==""){
		std::stringstream ss;
		ss<<count;
		name = string("Printer ")+ss.str();
	}
}

template<typename T>
Print<T>::Print(BaseNode<T>* _child, const string& _name):name(_name){
	Print<T>::child = _child;
	Print<T>::count++;
	if(_name==""){
		std::stringstream ss;
		ss<<count;
		_name = string("Printer ")+ss.str();
	}
}

template<typename T>
T Print<T>::eval(){
	if(this->evaled)return this->value;
	T ans = this->child->eval();
	std::cout<<"Print Operator : "<<name<<" = "<<ans<<std::endl;
	this->value = ans;
	this->evaled = true;
	return ans;
}

template<typename T>
string Print<T>::getName(){
	return name;
}

template<typename T>
void Print<T>::setName(const string& _name){
	name = _name;
}
