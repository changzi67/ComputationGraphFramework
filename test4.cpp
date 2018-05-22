#include <iostream>
#include <ctime>
#include "BaseNode.h"
#include "Constant.h"
#include "Placeholder.h"
#include "Multiply.h"

using namespace std;

const int maxn = 3e5;
BaseNode<float>* arr[maxn];

int main(int argc, char const *argv[])
{
	auto a = Constant<float>(1);
	auto x = Placeholder<float>("x");
	arr[0] = new Multiply<float>(a,x);
	arr[1] = new Multiply<float>(x,*arr[0]);
	for(int i=2;i<maxn;++i){
		arr[i] = new Multiply<float>(arr[i-2],arr[i-1]);
	}
	cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
	cout<<arr[maxn-1]->eval({{x,-1}})<<endl;

	cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}
