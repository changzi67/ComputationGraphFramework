#include "Meow.h" 
#include "Newton.h"
#include <bits/stdc++.h> 
int main() 
{
    //样例1：原测试文件 能正常运行 （在默认的session下）
    /*auto x = Placeholder("x");
    auto y = Variable(1);
    auto res = x + y;
    std::cout << res.Eval({{"x", 1}}).Print() << '\n';
    y.Set(2);
    std::cout << res.Eval({{"x", 1}}).Print() << '\n';
    y.Add(1);
    std::cout << res.Eval({{"x", 1}}).Print() << '\n';
    y.Sub(1);
    std::cout << res.Eval({{"x", 1}}).Print() << '\n';
    y.Mul(3);
    std::cout << res.Eval({{"x", 1}}).Print() << '\n';
    y.Div(3);
    std::cout << res.Eval({{"x", 1}}).Print() << '\n';
*/
    //样例二：正经的session
/*    Session s1;
    Session s2;
    auto x = Placeholder("x");
    auto z = Variable(2, s2);
    auto y = Variable(1, s1);
    auto res = x + y;
    std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';
      //y.Set(2);   默认为在创建时的Session执行；
  s1.add(y, 1);  // 这是另一种接口(推荐)
                   // 可以让一个Variable在多个Session中分别绑定不同的值

    std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';
    // 但eval的时候就必须在Session下才能进行操作了，第一阶段样例代码是因为他创建的时候缺省Session
    // 如果这儿不在Sesseion下操作会报错

    s1.add(y, 1);
    std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';
    s1.sub(y, 1);
    std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';
    s1.mul(y, 3);
    std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';
    s1.div(y, 3);
    std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';

    // 三：以下为测试存储到文件和读取
    s1.Save("save_net.cpkt");
    s1.Clear();
    //std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';
    s1.Restore("save_net.cpkt");
    std::cout << res.Eval({{"x", 1}}, s1).Print() << '\n';
    return 0;
*/

	/*auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto t1 = x * y;
	auto t4 = Ln(x);
	auto t5 = t4 / t1;
	auto g = t5.Grad();
	auto res = g[x].Grad();

	std::cout << res[x].Eval({{"x", 3}, {"y", 2}}).Print()<< std::endl;*/


	std::cout << Solve({1,0,3,2,1,1}) <<std::endl;

	/*auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto z = Sin(x * y);
	auto g = z.Grad();
	std::cout << g[x].Eval({{"x", 3}, {"y", 2}}).Print()<< std::endl;*/

	auto x = Placeholder("x");
    auto y = Placeholder("y");
    auto z = Constant(3);
    auto z1 = Sin(z);
    auto z2 = Ln(y);
    auto t = z1 + z2;
    auto x2 = Exp(x);
    auto res = t * x2;
    std::cout << res.Eval({{"x", 1}, {"y", 3}}).Print()<< std::endl;
    auto test =Assert( x > z );
    auto test2 = Bind (t, test);
    auto test3 = x>z;
    std::cout << t.Eval({{"x", 1}, {"y", 0.01}}).Print()<< std::endl;
    std::cout << test2.Eval({{"x", 1}, {"y", 0.01}}).Print()<< std::endl;
    return 0;
}
