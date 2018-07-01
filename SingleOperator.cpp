#include "SingleOperator.h"
#include "Constant.h"
#include "DoubleOperator.h"

Node& Gra::operator[](Node &graded) {
	if (grads.find(&graded) == grads.end())
	{
		throw std::domain_error("The Node in the square bracket is constant or not related.");
	}
	else
	{
		return *grads[&graded];
	}
}

Tensor SingleOperator::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		value=calc(A);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

Tensor* Quadratic::calc(const Tensor& A)
{
	if(!(A.Type()))
		throw std::invalid_argument("Error : Quadratic_Cost node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") !");
	return new Tensor(A.Quadratic_Cost());
}

Tensor* Sigmoid::calc(const Tensor& A)
{
	Tensor *tmp=new Tensor(A);
	tmp->Sigmoid();
	return tmp;
}

Tensor* Ln::calc(const Tensor &A) {
	if (A < 0) throw std::domain_error("Error :  log operator's input must be positive.");
	return new Tensor(ln(A));
}

Tensor* Sig_grad::calc(const Tensor &A) {
	Tensor *tmp = new Tensor(A);
	tmp->sig_grad();
	return tmp;
}

// ！这里的内部实现做了改动，因为在后续求导过程中为了多态，需要标量也能transpose
// 改成了标量也可绑定transpose节点，值是自身
Tensor* Transpose::calc(const Tensor& A)
{
    Tensor *tmp = nullptr;
	if(!A.Type()) {
        tmp=new Tensor(A);
	}
	else {
	    tmp=new Tensor(A.M(),A.N());
        tmp->Transpose(A);
	}
	return tmp;
}

Tensor* Assert::calc(const Tensor& A)
{
	if(A<=Tensor(0))
		std::cout<<"Error: Assertion failed"<<std::endl;
	return new Tensor(0);
}

void Ln::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Constant(1);
	grads[a].insert(&(t * (*temp / *a)));
	a->grad(grads, t * (*temp / *a));
}

void Sin::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Cos(*a);
	grads[a].insert(&(t * *temp));
	a->grad(grads, t * *temp);
}

void Cos::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp1 = new Sin(*a);
	Node * temp2 = new Constant(-1);
	grads[a].insert(&(t * *temp1 * *temp2));
	a->grad(grads, t * *temp1 * *temp2);
}

void Exp::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node *temp = new Exp(*a);
	grads[a].insert(&(t * *temp));
	a->grad(grads, t * *temp);
}

void Sigmoid::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Sig_grad(*a);
	Node * ans = new Dmul(*temp, t);
	grads[a].insert(ans);
	a->grad(grads, *ans);
}

void Quadratic::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Constant(2);
	grads[a].insert(&(t * (*temp * *a)));
	a->grad(grads, t * (*temp * *a));
}
