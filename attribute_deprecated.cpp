#include <iostream>

struct [[deprecated]] MyStruct {};
[[deprecated("for some reason")]] static int g_val{0};

int main() {
  MyStruct s;
  std::cout << g_val << "\n";
}
