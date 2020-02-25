// testCPP14.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <iostream>
#include <tuple>
#include <functional>
//https://stackoverflow.com/questions/30940504/simplest-c-example-to-verify-my-compiler-is-c14-compliant
auto f() // this function returns multiple values
{
  int x = 5;
  return std::make_tuple(x, 7); // not "return {x,7};" because the corresponding
								// tuple constructor is explicit (LWG 2051)
}
auto func(int i)
{
  return[i = std::move(i)](int b){return b + i; };
}

int main()
{
  int num = func(3)(5);
  printf("num %d\n",num);
  printf("%ld\n", __cplusplus);     
#if __cplusplus < 201300
//#error I require C++14 for this code, so die.
#endif
  // heterogeneous tuple construction
  int n = 1;
  auto t = std::make_tuple(10, "Test", 3.14, std::ref(n), n);
  n = 7;
  std::cout << "The value of t is " << "("
	<< std::get<0>(t) << ", " << std::get<1>(t) << ", "
	<< std::get<2>(t) << ", " << std::get<3>(t) << ", "
	<< std::get<4>(t) << ")\n";

  // function returning multiple values
  int a, b;
  std::tie(a, b) = f();
  std::cout << a << " " << b << "\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
