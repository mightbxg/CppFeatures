#include <Eigen/Core>
#include <cmath>
#include <iostream>
#include <vector>

// lambda 表达式可以在定义的时候立即执行，这种用法被称为“立即执行函数表达式”
// (Immediately-invoked function expression, IIFE),
// 能够起到复杂初始化、变量隔离、简化代码、使代码结构更清晰等作用

struct OneFloat {
  float val{0.0f};
  OneFloat() { std::cout << "OneFloat default ctor" << std::endl; }
  explicit OneFloat(float v) : val(v) {
    std::cout << "OneFloat ctor with " << val << std::endl;
  }
  OneFloat& operator=(const OneFloat& rhs) {
    val = rhs.val;
    std::cout << "OneFloat copy assign " << val << std::endl;
    return *this;
  }
};

struct MyStruct {
  OneFloat var{0.0f};
  // OneFloat 两次构造 & 一次拷贝
  MyStruct(bool flag1, bool flag2) {
    float a = flag1 ? 1.0 : 2.0;
    float b = flag2 ? 3.0 : 4.0;
    var = OneFloat(std::pow(b, a));
  }
};

struct MyStructIIFE {
  OneFloat var{0.0f};
  // OneFloat 只有一次构造
  MyStructIIFE(bool flag1, bool flag2)
      : var([flag1, flag2] {  // 复杂初始化
          float a = flag1 ? 1.0 : 2.0;
          float b = flag2 ? 3.0 : 4.0;
          return std::pow(b, a);
        }()) {}
};

std::vector<std::vector<std::vector<int>>> load_data() { return {}; }
void some_other_function(bool) {}

void func() {
  bool has_zero = false;
  auto temp_data = load_data();
  for (const auto& vss : temp_data) {
    for (auto& vs : vss) {
      for (auto v : vs) {
        if (v == 0) {
          has_zero = true;
          break;
        }
      }
      if (has_zero) break;
    }
    if (has_zero) break;
  }
  // some other operations
  some_other_function(has_zero);
}

void func_IIFE() {
  auto has_zero = [&]() -> bool {
    auto temp_data = load_data();  // 变量隔离
    for (const auto& vss : temp_data) {
      for (auto& vs : vss) {
        for (auto v : vs) {
          if (v == 0) return true;  // 简化代码
        }
      }
    }
    return false;
  }();
  // some other operations
  some_other_function(has_zero);
}

int main() {
  // 复杂初始化
  static const Eigen::Matrix2f R = [] {
    Eigen::Matrix2f mat;
    mat << 0, 1, -1, 0;
    return mat;
  }();

  std::cout << "MyStruct ----------------\n";
  MyStruct s1(false, true);
  std::cout << "MyStructIIFE ------------\n";
  MyStructIIFE s2(false, true);
  std::cout << "\n";
  func();
  func_IIFE();
}