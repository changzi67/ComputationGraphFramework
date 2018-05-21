#pragma once
#include "BaseNode.h"

template <typename T>
class Parameter: public BaseNode<T>
{
public:
	Parameter() = delete;
	Parameter(const T& data);
	virtual T eval();
	void set(const T& data);
	void add(const T& data);
	void minus(const T& data);
	void multiply(const T& data);
	void divide(const T& data);
	~Parameter(){}
};

template<typename T>
Parameter<T>::Parameter(const T& data){
	Parameter::timeStamp = ComputationGraph::currentTime++;
	Parameter<T>::value = data;
}

template<typename T>
T Parameter<T>::eval(){
	return this->value;
}

template<typename T>
void Parameter<T>::set(const T& data){
	Parameter<T>::timeStamp = ComputationGraph::currentTime++;
	this->value = data;
}

template<typename T>
void Parameter<T>::add(const T& data){
	Parameter<T>::timeStamp = ComputationGraph::currentTime++;
	this->value =this->value + data;
}

template<typename T>
void Parameter<T>::minus(const T& data){
	Parameter<T>::timeStamp = ComputationGraph::currentTime++;
	this->value = this->value - data;
}

template<typename T>
void Parameter<T>::multiply(const T& data){
	Parameter<T>::timeStamp = ComputationGraph::currentTime++;
	this->value = this->value * data;
}

template<typename T>
void Parameter<T>::divide(const T& data){
	Parameter<T>::timeStamp = ComputationGraph::currentTime++;
	this->value = this->value / data;
}
