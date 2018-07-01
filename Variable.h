#ifndef VARIABLE
#include "Node.h"
#define VARIABLE
class Variable:public Node
{
private:
	Session* sess;
	Tensor eval(std::map<std::string,Tensor>&, Session& s) override;
	void Release(){}
public:
	virtual void grad(std::map<Node, std::multiset<Node&>>, Node&) {}
	Variable(const Tensor& _t, Session& s = root, const std::string& _nm="");
	Variable( Session& s = root, const std::string& _nm="");
	Variable(const int& n,const int& m, Session& s = root, const std::string& _nm="");
	
	std::string Expr()
	{
		return std::string("Variable(")+name+")";
	}

	void grad (Node * Graded) {}
	void Rely(std::set<std::string>& lib){}
	void Set(const Tensor& t);   // 默认加减乘除在构造时的session下
	void Add(const Tensor& t);   // 但实际上一个Variable可在多个Session中取不同值
	void Sub(const Tensor& t);   // 比如可以构建 y (1, s1);之后 y.Set(2, s2)
	void Mul(const Tensor& t);
	void Div(const Tensor &t);
	Variable& operator +=(const Tensor &t){Add(t);return *this;}
	Variable& operator -=(const Tensor &t){Sub(t);return *this;}
	Variable& operator *=(const Tensor &t){Mul(t);return *this;}
	Variable& operator /=(const Tensor &t){Div(t);return *this;}
	
	Tensor Value(Session& s = root);
};

#endif
