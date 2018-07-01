#pragma once
#include "Meow.h"
#include <iostream>
#include <vector>
#include <cmath>
using std::cout;
using std::endl;
using std::vector;

double Solve(const vector<double>& facts, double init = -1 );


double Solve(const vector<double>& facts, double init) {//facts 为多项式系数，高次项在前，0记得空出来
	if(facts.empty())
		throw std::invalid_argument("No equation given\n");
	auto x = Placeholder("x");
	Node* temp = new Constant(facts[0]);
	for(int i = 1;i < facts.size(); ++i) {
		temp = &((* new Constant(facts[i])) + ((*temp)*x));
	}
	auto g = temp->Grad();
	double cur = init;
	const double eps = 1e-6;
	double prev;
	do {
		prev = cur;
		double res = temp->Eval({{"x" , cur}});
		double grad = g[x].Eval({{"x", cur}});
		cur = cur - res/grad;
		std::cout<< cur <<endl;
	}while(abs(cur-prev)>eps);
	return cur;
}
