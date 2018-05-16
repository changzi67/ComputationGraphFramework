#include "Parameter.h"

template<typename T>
T Parameter<T>::eval(){
	return this->value;
}

template<typename T>
void Parameter<T>::set(const T& data){
	this->value = data;
}

template<typename T>
void Parameter<T>::add(const T& data){
	this->value =this->value + data;
}

template<typename T>
void Parameter<T>::minus(const T& data){
	this->value = this->value - data;
}

template<typename T>
void Parameter<T>::multiply(const T& data){
	this->value = this->value * data;
}

template<typename T>
void Parameter<T>::divide(const T& data){
	this->value = this->value / data;
}
