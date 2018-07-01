#ifndef DOUBLEOPERATOR
#include "Node.h"
#include "Variable.h"
#define DOUBLEOPERATOR  
class Add:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&)const; 
	Tensor eval(std::map<std::string,Tensor>&, Session& sess) override;
	void Release(); 
public:
	Add(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Add(const Add &t)=default;
	
	Add(Add &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}

    void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;

	std::string Expr()
	{
		return "("+a->Expr()+"+"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	
};

class Sub:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor& ,const Tensor& );
	Tensor eval(std::map<std::string,Tensor>&, Session& sess);
	void Release();
public:
	Sub(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Sub(const Sub &t)=default;

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	
	Sub(Sub &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()	
	{
		return "("+a->Expr()+"-"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	
};

class Mul:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor& ,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>&, Session& sess);
	void Release();
public:
	Mul(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Mul(const Mul &t)=default;
	Mul(Mul &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}

	void grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t) override;
	
	std::string Expr()
	{
		return "("+a->Expr()+"*"+b->Expr()+")";
	}
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

// A中每一个元素分别乘B中对应元素，该类用于Sigmoid函数的求导
class Dmul : public Node
{
private:
	Node *a,*b;
	Tensor eval(std::map<std::string,Tensor>& Inputs, Session& sess);
	void Release() override;
public:
	Dmul(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}

	Dmul(const Dmul &t)=default;

	Dmul(Dmul &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}

	std::string Expr()
	{
		return "("+a->Expr()+"/*/"+b->Expr()+")";
	}

	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Div:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>& Inputs, Session& sess);
	void Release();
public:
	Div(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Div(const Div &t)=default;

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	
	Div(Div &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"/"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Pow:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>&, Session& sess);
	void Release();
public:
	Pow(Node &_a,Node &_b,const std::string &_nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Pow(const Pow &t)=default;

	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override {};
	
	Pow(Pow &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"^"+b->Expr()+")";
	}



	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Less:public Node
{
private:
	Node *a,*b;
	//void Judge(const Tensor&,const Tensor&)const; 
	Tensor eval(std::map<std::string,Tensor>&, Session& sess);
	void Release(); 
public:
	Less(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Less(const Less &t)=default;
	
	Less(Less &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}

    void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;

	std::string Expr()
	{
		return "("+a->Expr()+"<"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	
};

class LessEq:public Node
{
private:
	Node *a,*b;
	//void Judge(const Tensor&,const Tensor&)const; 
	Tensor eval(std::map<std::string,Tensor>&, Session& sess);
	void Release(); 
public:
	LessEq(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	LessEq(const LessEq &t)=default;
	
	LessEq(LessEq &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}

    void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;

	std::string Expr()
	{
		return "("+a->Expr()+"<="+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	
};

class Assign :public Node
{
private:
	Variable *a;
	Node *b;
	Tensor eval(std::map<std::string,Tensor>&, Session&) override;
public:
	Assign(Variable &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Assign(const Assign &t)=default;
	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	
	void Release() override;
	std::string Expr() override
	{
		return "Assign( "+ a->Expr() +"<-" + b->Expr()+")";
	}

	void Rely(std::set<std::string>& lib) override
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Bind :public Node
{
private:
	Node *a;
	Node *b;
	Tensor eval(std::map<std::string,Tensor>&, Session&) override;
public:
	Bind(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Bind(const Bind &t)=default;
	void grad(std::map<Node*, std::multiset<Node*>>&, Node&) override;
	
	void Release() override;
	std::string Expr() override
	{
		return "Bind (" + a->Expr()+ ","+ b->Expr() +")";
	}

	void Rely(std::set<std::string>& lib) override
	{
		a->Rely(lib);
		b->Rely(lib);
	}

};

inline Add& operator +(Node& A, Node& B)
{
	Add* tmp=new Add(A,B);
	return *tmp;
} 

inline Sub& operator -(Node& A,Node& B)
{
	Sub* tmp=new Sub(A,B);
	return *tmp;
}

inline Mul& operator *(Node& A, Node& B)
{
	Mul* tmp=new Mul(A,B);
	return *tmp;
}

inline Div& operator /(Node& A,Node& B)
{
	Div* tmp=new Div(A,B);
	return *tmp;
}

inline Pow& operator ^(Node& A,Node& B)
{
	Pow* tmp=new Pow(A,B);
	return *tmp;
}

inline Less& operator <(Node& A, Node& B)
{
	return *(new Less(A,B));
}

inline Less& operator >(Node& A, Node& B)
{
	return *(new Less(B,A));
}

inline LessEq& operator <=(Node& A, Node& B)
{
	return *(new LessEq(A,B));
}

inline LessEq& operator >=(Node& A, Node& B)
{
	return *(new LessEq(B,A));
}


#endif