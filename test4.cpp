#include <iostream>
#include <ctime>
#include "BaseNode.h"
#include "Constant.h"
#include "Placeholder.h"
#include "Add.h"

using namespace std;

const int maxn = 3e5;
//1e5秒出，3e5会爆栈
//然而我的windows没到1e5就爆栈了……可以考虑编译选项加上开栈
BaseNode<float>* arr[maxn];

int main(int argc, char const *argv[])
{
	auto a = Constant<float>(1);
	auto x = Placeholder<float>("x");
	arr[0] = new Add<float>(a,x);
	arr[1] = new Add<float>(x,*arr[0]);
	for(int i=2;i<maxn;++i){
		arr[i] = new Add<float>(arr[i-2],arr[i-1]);
	}
	cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
	//3e5项的斐波那契，的确能证明时间复杂度没有到指数级，然而答案是inf
	cout<<arr[maxn-1]->eval({{x,1}})<<endl;
	
	cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}
