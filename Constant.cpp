#include "Constant.h"

Tensor Constant::eval(std::map<std::string,Tensor>&Inputs, Session& sess) {
	if(debug)
	{
		std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
		std::cout<<value->Print()<<'\n';
	}	
	return *value;
}

void Constant::grad(std::map<Node *, std::multiset<Node *>> &grads, Node &t) {
	if (grads.find(this) != grads.end())
	    grads.erase(grads.find(this));
}
