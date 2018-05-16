#include "BaseNode.h"
#include "Placeholder.h"

#include <initializer_list>
#include <string>
#include <iostream>


//using initializer list to support something like t.eval({x=1,y=2});
template<typename T>
T BaseNode<T>::eval(const std::initializer_list<BaseNode<T>&>& vars){
	try{
		T ans = eval();
	}
	catch(const string & s){
		std::cout<<"Error: Placeholder "<<s<<"not found!"<<std::endl;
	}
	for(auto it = vars.begin();it!=vars.end();++it){
		*it.setAssigned(false);
	}
	return ans;
}
