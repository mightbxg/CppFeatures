#pragma once

#include <iostream>
#include <string>

// clang-format off
// https://en.cppreference.com/w/cpp/language/inline
// 内部链接 (internal linkage)：每个包含本头文件的翻译单元都有一个单独的实例，互不影响
// 外部链接 (external linkage)：每个包含本头文件的翻译单元共享同一实例
// C++17 引入的 inline variable 特性可以实现声明即定义的外部链接变量，更加便捷且能避免重复定义问题

static int a_static{0};  // 内部链接

const int a_const{0};  // 内部链接，且无法修改

extern int a_extern;  // 外部链接，仅作为变量声明，有且仅能有一个翻译单元存在变量定义

inline int a_inline{0};  // 外部链接，声明即定义

inline static int a_inline_static{0};  // 内部链接，等价于没有 inline

struct MyStruct {
  static int m_static;  // 外部链接，仅作为变量声明，有且仅能有一个翻译单元存在变量定义
  inline static int m_inline_static{0};  // 外部链接，声明即定义
};

inline void Print(const std::string& msg, const int& v, bool flag = false) {
  if (flag) std::cout << "\33[32m";
  std::cout << msg << ": " << &v << " " << v << "\33[0m\n";
}

void PrintVarAddress1();

// clang-format on
