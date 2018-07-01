#include "DoubleOperator.h"
#include "Constant.h"
#include "Meow.h"

void Add::Judge(const Tensor& A,const Tensor& B)const
{
	if(A.Type()!=B.Type()||(A.Type()&&B.Type()&&(A.N()!=B.N()&&A.N()!=1&&B.N()!=1)||(A.M()!=B.M()&&A.M()!=1&&B.M()!=1)))
		throw std::invalid_argument("Error : Add node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Add::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		//Judge(A,B);
		value=new Tensor(A+B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Add::grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t)
{
    grads[a].insert(&t);
	grads[b].insert(&t);

    a->grad(grads, t);
    b->grad(grads, t);
}

void Add::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Sub

void Sub::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Constant(-1);
	grads[a].insert(&t);
	grads[b].insert(&(*temp * t));

	a->grad(grads, t);
	b->grad(grads, *temp * t);
}

void Sub::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()!=B.Type()||(A.Type()&&(A.N()!=B.N()||A.M()!=B.M())))
		throw std::invalid_argument("Error : Sub node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Sub::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		//Judge(A,B);
		value=new Tensor(A-B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}		
	}
	return *value;
}

void Sub::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Mul
void Mul::grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t)
{
    grads[a].insert(&(t * *(new Transpose(*b))));
	grads[b].insert(&(*(new Transpose(*a)) * t));
	a->grad(grads, t * *(new Transpose(*b)));
	b->grad(grads, *(new Transpose(*a)) * t);
}

void Mul::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()&&B.Type()&&A.M()!=B.N())
		throw std::invalid_argument("Error : Mul node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Mul::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		Judge(A,B);
		value=new Tensor(A*B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Mul::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Div

void Div::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp1 = new Constant(1);
	Node * temp2 = new Constant(-1);
	grads[a].insert(&(t * (*temp1 / *b)));
	grads[b].insert(&(t * (*a * *temp2 / *b / *b)));
	a->grad(grads, t * (*temp1 / *b));
	b->grad(grads, t * (*a * *temp2 / *b / *b));
}

void Div::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Div node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Div::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		Judge(A,B);
		value=new Tensor(A/B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Div::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//Pow
void Pow::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Pow node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Pow::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		Judge(A,B);
		value=new Tensor(pow(A,B));
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Pow::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

Tensor Less::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		//Judge(A,B);
		value=new Tensor(A<B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Less::grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t)
{
	//emmmm……暂时不知道咋整
	//单位冲激是对的然而炼丹的时候也没用
	//就当它是零吧
}

void Less::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

Tensor LessEq::eval(std::map<std::string,Tensor>& Inputs, Session& sess)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		//Judge(A,B);
		value=new Tensor(A<=B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void LessEq::grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t)
{
	//emmmm……暂时不知道咋整
	//单位冲激是对的然而炼丹的时候也没用
	//就当它是零吧
}

void LessEq::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

Tensor Assign::eval (std::map<std::string, Tensor> & Inputs, Session& sess) {
	if(value==nullptr){
		Tensor B=b->eval(Inputs, sess);
		value=new Tensor(B);
	}
	return *value;
}

void Assign::Release() {
	a->Set(*value);
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

void Assign::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	grads[b].insert(&t);
	b->grad(grads, t);
}

Tensor Bind::eval (std::map<std::string, Tensor> & Inputs, Session& sess) {
	if(value==nullptr){
		Tensor A=a->eval(Inputs, sess);
		b->eval(Inputs, sess);
		value=new Tensor(A);
	}
	return *value;
}

void Bind::Release() {
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

void Bind::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	grads[a].insert(&t);
	a->grad(grads, t);
}

Tensor Dmul::eval(std::map<std::string, Tensor> &Inputs, Session &sess) {
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs, sess);
		Tensor B=b->eval(Inputs, sess);
		value = new Tensor(dmul(A, B));
	}
	return *value;
}

void Dmul::Release() {
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}