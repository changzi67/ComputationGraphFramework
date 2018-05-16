#include "BaseNode.h"
#include "Placeholder.h"
#include <string>
#include <sstream>
using std::string;

template <typename T>
Placeholder<T>::Placeholder(const string & _name):name(_name),assigned(false){
	count++;
	if(name==""){
		std::stringstream ss;
		ss<<count;
		name = string("Placeholder ")+ss.str();
	}
}

template <typename T>
T Placeholder<T>::eval(){
	if(assigned)
		return this->value; //value may be undefined because of specializing
	else throw(name);
}

template<typename T>
void Placeholder<T>::setAssigned(bool status){
	assigned = status;
}

template<typename T>
const Placeholder<T>& Placeholder<T>::operator = (const T& data){
	this->value = data;
	setAssigned(true);
	return *this;
} 

template<typename T>
string Placeholder<T>::getName(){
	return name;
}

template<typename T>
void Placeholder<T>::setName(const string & _name){
	name = _name;
}