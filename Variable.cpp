#include "Variable.h" 

Variable::Variable(const Tensor &_t, Session &s, const std::string &_nm) :Node(_nm), sess(&s){
	s.ins(this, new Tensor(_t));
}

Variable::Variable(Session &s, const std::string &_nm) :Node(_nm), sess(&s) {
	s.ins(this, new Tensor());
}

Variable::Variable(const int &n, const int &m, Session &s, const std::string &_nm) :Node(_nm), sess(&s) {
	s.ins(this, new Tensor(n,m));
}

Tensor Variable::eval(std::map<std::string,Tensor>&Inputs, Session& sess)
{
	Tensor * va = sess.get_value(this);
	if(debug)
	{
		std::cout<<"Print Operator:"<<name<<"("<<va->PrintType()<<")="<<Expr()<<'\n';
		std::cout<<va->Print()<<'\n';
	}	
	return *va;
}

void Variable::Set(const Tensor& t)
{
	Tensor * va = sess -> get_value(this);
	if(t.Type()!=va->Type()||(t.Type()&&(t.N()!=va->N()||t.M()!=va->M())))
		throw std::invalid_argument("Error : Try to set a variable(" +va->PrintType()+") with Tensor("+t.PrintType()+")!");
	sess -> set(this, new Tensor(t));
}

void Variable::Add(const Tensor& t)
{
	Tensor * va = sess -> get_value(this);
//	if(t.Type()!=va->Type()||(t.Type()&&(t.N()!=va->N()||t.M()!=va->M())))
//		throw std::invalid_argument("Error : Try to Add a variable(" +va->PrintType()+") with Tensor("+t.PrintType()+")!");
	sess -> set(this, new Tensor(*va + t));
}

void Variable::Sub(const Tensor& t)
{
	Tensor * va = sess -> get_value(this);
//	if(t.Type()!=va->Type()||(t.Type()&&(t.N()!=va->N()||t.M()!=va->M())))
//		throw std::invalid_argument("Error : Try to Add a variable(" +va->PrintType()+") with Tensor("+t.PrintType()+")!");
	sess -> set(this, new Tensor(*va - t));
}

void Variable::Mul(const Tensor& t)
{
	Tensor * va = sess -> get_value(this);
//	if(t.Type()!=va->Type()||(t.Type()&&(t.N()!=va->N()||t.M()!=va->M())))
//		throw std::invalid_argument("Error : Try to Add a variable(" +va->PrintType()+") with Tensor("+t.PrintType()+")!");
	sess -> set(this, new Tensor(*va * t));
}

void Variable::Div(const Tensor &t)
{
	Tensor * va = sess -> get_value(this);
//	if(t.Type()!=va->Type()||(t.Type()&&(t.N()!=va->N()||t.M()!=va->M())))
//		throw std::invalid_argument("Error : Try to Add a variable(" +va->PrintType()+") with Tensor("+t.PrintType()+")!");
	sess -> set(this, new Tensor(*va / t));
}

Tensor Variable::Value(Session &s) {
	Tensor* va = s.get_value(this);
	{return *va;}
}