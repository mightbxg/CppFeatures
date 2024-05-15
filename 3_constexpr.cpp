#include <iostream>

// https://en.cppreference.com/w/cpp/language/constexpr
// 常量表达式就是能够在编译期间计算的表达式(函数或者变量)，其主要有几个很棒的特性：
//    1. 编译期间计算，节省运行时的计算量
//    2. 能够充当模板参数
//    3. 能提供类型安全、作用域、调试属性、函数性质，这些是 #define 无法提供的

#define SQUARE(X) X* X

#define MIN(a, b) a < b ? a : b
constexpr int min(int a, int b) { return a < b ? a : b; }

int main() {
  int radius = 5;
  double area = 3.14 * radius * radius;
  std::cout << area << "\n";

  auto a = MIN("abc", "def");
  std::cout << a << "\n";
}
