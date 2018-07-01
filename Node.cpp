#include "Node.h"
#include "Constant.h"
#include "SingleOperator.h"
#include "DoubleOperator.h"


std::string Node::PrintRely()
{
	std::string ans=name+" rely on:\n";
	std::set<std::string> lib;
	lib.clear();
	Rely(lib);
	if(lib.empty())ans+="\tNOTHING\n";
	for(auto it=lib.cbegin();it!=lib.cend();it++) 
		ans+="\t"+*it+"\n";
	return ans;
}

Gra& Node::Grad()
{
    std::map<Node*, std::multiset<Node*>> grads;
    grads.clear();
	grad(grads, *(new Constant(1)));

	std::map<Node*, std::multiset<Node*>>::iterator it;
	it = grads.begin();

	std::map<Node*, Node*> g;

	while(it != grads.end())
	{
		auto iter=(it -> second).begin();
		Node* temp = *(iter);
		++iter;

		while(iter!=(it -> second).end())
		{
			temp = &(*temp + *(*(iter)));
			++iter;
		}
		g[it -> first] = temp;
		it ++;
	}
	Gra * t = new Gra(*this, g);
	return *t;
}

Tensor Node::Eval(std::map<std::string,Tensor>&Inputs, Session& s)
{
	Tensor ans=eval(Inputs, s);
	Release();
	return ans;
}

Tensor Node::Eval(const std::initializer_list<std::pair<std::string,Tensor>>& il, Session& s)
{
	std::map<std::string,Tensor> Inputs;
	for(auto it=il.begin();it!=il.end();it++)
	{
		if(Inputs.find(it->first)!=Inputs.end())
			throw std::invalid_argument("Error : Redeclaration in inputs!");
		Inputs[it->first]=it->second;
	}
	return Eval(Inputs, s);
}
