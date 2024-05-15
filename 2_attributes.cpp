#include <iostream>

// https://en.cppreference.com/w/cpp/language/attributes
// “属性”是一种用于提供关于变量、函数、类、命名空间、表达式等的额外信息的机制。
// 这些属性可以被编译器或其他工具用于优化代码、生成警告或错误、或者改变代码的行为。

/***************************************************************/
// [[nodiscard]]: 用于修饰函数，表明该函数返回值不应该被舍弃（比如常函数）

struct MyStructA {
  explicit MyStructA(int val) : val_(val) {}
  [[nodiscard]] int get_val() const { return val_; }

 private:
  int val_{0};
};

void example_nodiscard() {
  MyStructA s(10);
  s.get_val();  // 不应被丢弃的函数返回值
}

/***************************************************************/
// [[deprecated]]: 可以修饰函数、类、变量等，将其标记为已弃用

struct [[deprecated]] MyStructB {
  int val{0};
};
[[deprecated("for some reason")]] static int g_val{0};

void example_deprecated() {
  MyStructB s;  // 被弃用的结构体
  std::cout << s.val << "\n";
  std::cout << g_val << "\n";  // 被弃用的变量
}

/***************************************************************/
// [[maybe_unused]]: 可以修饰函数、类、变量，阻止编译器报出“未使用的xxx”警报

static void func1() {}  // 未被使用的静态函数
[[maybe_unused]] static void func2() {}

void example_maybe_unused() {
  int v1 = 0;  // 未被使用的变量
  [[maybe_unused]] int v2 = 0;
}

int main() {
  example_nodiscard();
  example_deprecated();
  example_maybe_unused();
}