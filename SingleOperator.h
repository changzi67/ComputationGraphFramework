#ifndef SINGLEOPERATOR
#include "Node.h"
#define SINGLEOPERATOR
class SingleOperator:public Node
{
protected:
	Node *a;
	virtual Tensor* calc(const Tensor&)=0;
	Tensor eval(std::map<std::string,Tensor>&, Session& sess);
	void Release()
	{
		a->Release();
		if(value!=nullptr)
		{
			delete value;
			value=nullptr;
		}
	}

public:

	SingleOperator(const std::string& _nm,Node &_a):Node(_nm),a(&_a){}
	void Rely(std::set<std::string>& lib){a->Rely(lib);}
};

class Gra : public SingleOperator {
private:
    Tensor* calc(const Tensor& A) override {throw std::invalid_argument("Grad operator for a node cannot be operated.");}
	std::map<Node*, Node*> grads;

public:
	Gra (Node& _a, std::map<Node*, Node*>& _grads) : SingleOperator("", _a), grads(_grads) {}
	Node& operator[] (Node& graded);
    std::string Expr() override {
        //std::cerr << "hhhhhhh";
        return "The Grad is " + a->Expr();
    }
};

class Exp:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(exp(A));}
public:
	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	Exp(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "exp("+a->Expr()+")";
	}
};

class Ln:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A) override ;
public:

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	Ln(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "ln("+a->Expr()+")";
	}
};

class Sin:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(sin(A));}
public:

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	Sin(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "sin("+a->Expr()+")";
	}
};

class Cos:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(cos(A));}
public:

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	Cos(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "cos("+a->Expr()+")";
	}
};

class Tan:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(tan(A));}
public:
	Tan(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "tan("+a->Expr()+")";
	}
};

class Asin:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(asin(A));}
public:
	Asin(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "asin("+a->Expr()+")";
	}
};

class Acos:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(acos(A));}
public:
	Acos(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "acos("+a->Expr()+")";
	}
};

class Atan:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(atan(A));}
public:
	Atan(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "atan("+a->Expr()+")";
	}
};

class Quadratic:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Quadratic(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	std::string Expr()
	{
		return "Quadratic_Cost("+a->Expr()+")";
	}
};

class Sigmoid:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Sigmoid(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	std::string Expr()
	{
		return "Sigmoid("+a->Expr()+")";
	}
};

class Transpose:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Transpose(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "("+a->Expr()+")^T";
	}
};

class Sig_grad : public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Sig_grad(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}

	std::string Expr() override
	{
		return "Sig_grad("+a->Expr()+")";
	}
};

class PowC:public SingleOperator
{
private:
	double c;
	Tensor* calc(const Tensor& A)override{return new Tensor(pow(A,c));}
public:
	PowC(Node &_a,double _c,const std::string& _nm=""):SingleOperator(_nm,_a),c(_c){}
	
	double C(){return c;}
	
	std::string Expr()
	{
		std::string pc=std::to_string(c);
		return "("+a->Expr()+"^"+pc+")";
	}
};

class Assert:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Assert(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "Assert("+a->Expr()+")";
	}
};

#endif
