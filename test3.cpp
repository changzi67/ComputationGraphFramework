#include <iostream>
#include <string>
#include "BaseNode.h"
#include "Placeholder.h"
#include "Parameter.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
	auto x = Placeholder<float>("x");
	auto y = Parameter<float>(1);
	auto res = x+y;
	cout<<res.eval({{x,1}})<<endl;
	y.set(2);
	cout<<res.eval({{x,1}})<<endl;
	y.add(1);
	cout<<res.eval({{x,1}})<<endl;
	y.minus(1.1);
	cout<<res.eval({{x,1}})<<endl;
	y.multiply(2);
	cout<<res.eval({{x,1}})<<endl;
	y.divide(2);
	cout<<res.eval({{x,1}})<<endl;
	return 0;
}