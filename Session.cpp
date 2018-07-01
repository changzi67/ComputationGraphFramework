#include "Session.h"
#include "Tensor.h"
#include <map>
#include <fstream>
#include <iostream>

Session root;

void Session::ins(Variable *a, Tensor *b) {
    data.insert(std::make_pair(a, b));
}

Tensor * Session::get_value(Variable * a) {
    if(data.find(a) == data.end()) {
        throw std::domain_error("Error : Your variable is not designated in this session."+name);
    }
    else return data[a];
}

void Session::set(Variable * a, Tensor * b) {
    data[a] = b;
}

void Session::add(Variable & a, const Tensor &t) {
    data[&a] = new Tensor(*data[&a] + t);
}

void Session::sub(Variable & a, const Tensor &t) {
    data[&a] = new Tensor(*data[&a] - t);
}

void Session::mul(Variable & a, const Tensor &t) {
    data[&a] = new Tensor(*data[&a] * t);
}

void Session::div(Variable & a, const Tensor &t) {
    data[&a] = new Tensor(*data[&a] / t);
}

void Session::Erase(Variable &a) {
    data.erase(&a);
}

void Session::Clear() {
    data.clear();
}

void Session::Save(std::string path) {
    std::ofstream fout(path, std::ios::binary);
    auto it = data.begin();
    while (it != data.end()) {
        fout.write((char*)&(it->first), sizeof(it->first));
        fout.write((char*)&(it->second), sizeof(it->second));
        it++;
    }
    fout.close();
}

void Session::Restore(std::string path) {
    //data.clear();
    std::ifstream fin(path, std::ios::binary);
    Variable* v = nullptr;
    Tensor* t = nullptr;
    while (!fin.eof()) {
        fin.read((char *)&v, sizeof(v));
        fin.read((char *)&t, sizeof(t));
        data.insert(std::make_pair(v, t));
    }
    fin.close();
}