#include <array>
#include <chrono>
#include <iostream>

// https://en.cppreference.com/w/cpp/language/constexpr
// 常量表达式就是能够在编译期间计算的表达式(函数或者变量)，其主要有几个很棒的特性：
//    1. 编译期间计算，节省运行时的计算量
//    2. 能够充当模板参数
//    3. 能提供类型安全、作用域、调试属性、函数性质，这些是 #define 无法提供的

/***************************************************************/

#define MIN(a, b) a < b ? a : b
constexpr int min(int a, int b) { return a < b ? a : b; }
int min_normal(int a, int b) { return a < b ? a : b; }

void example_min() {
  auto min_val1 = MIN("abc", "def");  // MIN本意是数字间比较
  // auto min_val2 = min("abc", "def"); // 因为类型校验而编译报错

  std::array<int, min(3, 4)> arr1 = {};  // constexpr函数返回值可作为模板参数
  // std::array<int, min_normal(3,4)> arr2 = {}; // 非constexpr函数不可以
}

/***************************************************************/

void example_area() {  // define容易出错，且作用域太广
#define RADIUS1 11.0
#define RADIUS2 RADIUS1 - 1.0
  constexpr double kRadius1 = 11.0;
  constexpr double kRadius2 = kRadius1 - 1.0;
  std::cout << "result of 3.14*10*10 -------------------------\n";
  std::cout << "   define: " << 3.14 * RADIUS2 * RADIUS2 << "\n";
  std::cout << "constexpr: " << 3.14 * kRadius2 * kRadius2 << "\n\n";
}

/***************************************************************/

static auto g_timepoint = std::chrono::high_resolution_clock::now();
void tic() { g_timepoint = std::chrono::high_resolution_clock::now(); }
void toc(const std::string& msg) {
  using namespace std::chrono;
  auto t = duration<double>(high_resolution_clock::now() - g_timepoint).count();
  std::cout << msg << t * 1e6 << " us\n";
}

uint64_t fibonacci_normal(uint64_t n) {  // 不可编译期间计算
  return n <= 1 ? n : fibonacci_normal(n - 1) + fibonacci_normal(n - 2);
}

constexpr uint64_t fibonacci(uint64_t n) {  // 可编译期间计算
  return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// 编译期间生成LUT查找表
constexpr unsigned kLutSize = 21;
static constexpr auto fib_lut = [] {
  std::array<uint64_t, kLutSize> lut = {};
  for (unsigned i = 0; i < kLutSize; ++i) {
    lut[i] = fibonacci(i);
  }
  return lut;
}();

void example_time() {
  constexpr uint64_t n = 20;
  std::cout << "time cost of fibonacci(" << n << ") -------------------\n";
  tic();
  const auto v1 = fibonacci_normal(n);
  toc("   normal: ");
  tic();
  const auto v2 = fibonacci(n);
  toc("constexpr: ");
  tic();
  const auto v3 = fib_lut[n];
  toc("      LUT: ");
  std::cout << "res: " << v1 << " vs " << v2 << " vs " << v3 << "\n";
}

/***************************************************************/

int main() {
  example_min();
  example_area();
  example_time();
}
