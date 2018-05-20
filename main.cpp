#include "BaseNode.h"
#include "Placeholder.h"
#include "Constant.h"
#include "Add.h"
#include "Sub.h"
#include "Multiply.h"
#include "Divide.h"


#include <iostream>
//#include <tuple>
using namespace std;

int main(int argc, char const *argv[])
{
	auto x = Placeholder<float>("x");
	auto y = Placeholder<float>("y");
	auto z = Constant<float>(3);
	auto t = y+z;
	auto res = t*(y+z);
	cout<<res.eval({{x,1.0},{y,2.0}})<<endl;
	
	cout<<res.eval({{x,1.0},{y,0.0}})<<endl;

	cout<<t.eval({{y,0.0}})<<endl;

	cout<<res.eval({{y,0.0}})<<endl;
	return 0;
}
