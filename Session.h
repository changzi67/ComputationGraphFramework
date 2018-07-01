#pragma once

#include <iostream>
#include <map>

class Variable;
class Tensor;

class Session {
private:
    std::string name;
    std::map<Variable*, Tensor*> data;
public:
    Session(const std::string& _nm="") : name(_nm) {data.clear();}
    Tensor* get_value(Variable*);
    void ins(Variable*, Tensor*);

    void set(Variable*, Tensor*);
    void add(Variable& a, const Tensor& t);   // 但实际上一个Variable可在多个Session中取不同值
    void sub(Variable& a, const Tensor& t);   // 比如可以构建 y (1, s1);之后 y.Set(2, s2)
    void mul(Variable& a, const Tensor& t);
    void div(Variable& a, const Tensor& t);

    void Erase(Variable& a);
    void Clear ();

    void Save(std::string);
    void Restore(std::string);

};

extern Session root;
