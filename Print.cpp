#include "Print.h"
#include <iostream>
#include <string>
#include <sstream>

using std::string;

template<typename T>
Print<T>::Print(const string& _name){
	Print<T>::count++;
	if(_name=""){
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
