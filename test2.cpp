#include <iostream>
#include <string>
#include "BaseNode.h"
#include "Placeholder.h"
#include "Print.h"


int main(int argc, char const *argv[])
{
	auto x = Placeholder<float>("x");
	auto y = Placeholder<float>("y");
	auto z = Placeholder<float>("z");
	auto t = Print<float>(x+y,"t");
	auto res = t+z;
	std::cout<<res.eval({{x,1},{y,3},{z,2}})<<std::endl;

	std::cout<<res.eval({{x,1},{y,2},{z,3}})<<std::endl;
	return 0;
}