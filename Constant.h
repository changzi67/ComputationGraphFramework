#ifndef CONSTANT
#define CONSTANT

#include "Node.h"

class Constant:public Node
{
private:
	Tensor eval(std::map<std::string,Tensor>&, Session& sess);
	void Release(){} 
public:
	Constant(const Tensor& _t,const std::string& _nm=""):Node(_nm,new Tensor(_t)){}
	std::string Expr()
	{
		return std::string("Constant(")+name+")";
	}
	void grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t) override;
	void Rely(std::set<std::string>& lib){}
};



#endif
